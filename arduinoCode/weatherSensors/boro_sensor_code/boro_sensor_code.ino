#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

//network configs
const char* ssid = "500102 2.4g";
const char* pass = "galati1923";

//Sensor lib configs
#include <SparkFunCCS811.h>
#include <SparkFunBME280.h>
#include <Wire.h>
#define CCS811_ADDR 0x5B

CCS811 myCCS811(CCS811_ADDR);
BME280 myBME280;

float temp_offset = -5.1; //offset temp reading to compensate for sensor heat

//db config
// Supabase API endpoint and key
const char* supabaseUrl = "https://supaapi.byteforce.ro/rest/v1";
const char* realtime_table = "sensor_realtime";
const char* arch_table = "dust_arch";
const char* supabaseKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJzZXJ2aWNlX3JvbGUiLAogICAgImlzcyI6ICJzdXBhYmFzZS1kZW1vIiwKICAgICJpYXQiOiAxNjQxNzY5MjAwLAogICAgImV4cCI6IDE3OTk1MzU2MDAKfQ.DaYlNEoUrrEn2Ig7tqibS-PHK5vgusbcbo7X36XVt4Q";
const char* bearer_key = "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJzZXJ2aWNlX3JvbGUiLAogICAgImlzcyI6ICJzdXBhYmFzZS1kZW1vIiwKICAgICJpYXQiOiAxNjQxNzY5MjAwLAogICAgImV4cCI6IDE3OTk1MzU2MDAKfQ.DaYlNEoUrrEn2Ig7tqibS-PHK5vgusbcbo7X36XVt4Q";
// the ID of the row
const char* id_rt = "2"; //1 = weather station; 2 = room sensor 

//json for caching data
const int capacity = JSON_OBJECT_SIZE(10);
StaticJsonDocument<capacity> wthr_data;
String serial_json;

//timer for archiving
unsigned long previousTime = 0;
unsigned long interval = 120000;


void setup() {
  Serial.begin(9600);
  Wire.begin();

  //connect to wifi
  Serial.print("Connecting");
  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    
   
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Connected :D \n");

  //Sensor setup ----------------------------
  //CCS811
  CCS811Core::status returnCode = myCCS811.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    Serial.println("Problem with CCS811");
    printDriverError(returnCode);
  }
  else
  {
    Serial.println("CCS811 online");
  }

  //BME280
  myBME280.settings.commInterface = I2C_MODE;
  myBME280.settings.I2CAddress = 0x77;
  myBME280.settings.runMode = 3; //Normal mode
  myBME280.settings.tStandby = 0;
  myBME280.settings.filter = 4;
  myBME280.settings.tempOverSample = 5;
  myBME280.settings.pressOverSample = 5;
  myBME280.settings.humidOverSample = 5;

  delay(10);  //sensor start-up
  byte id = myBME280.begin();
  if (id != 0x60)
  {
    Serial.println("Problem with BME280");
  }
  else
  {
    Serial.println("BME280 online");
  }

}

void cacheData()
{
  wthr_data.clear();
  serial_json.clear();

  wthr_data["CO2_ppm"] = myCCS811.getCO2();
  //Serial.print(myCCS811.getCO2());

  wthr_data["TVOC_ppb"] = myCCS811.getTVOC();
  //Serial.print(myCCS811.getTVOC());

  wthr_data["average_TEMP_celsius"] = myBME280.readTempC()+temp_offset;
  //Serial.print(myBME280.readTempC(), 1);

  wthr_data["PRESSURE_pascals"] = myBME280.readFloatPressure();
  //Serial.print(myBME280.readFloatPressure(), 2);

  wthr_data["HUMIDITY_percent"] = String(myBME280.readFloatHumidity(), 1);
  //Serial.print(myBME280.readFloatHumidity(), 0);

  //Write NULL for columns without input
  //wthr_data["dht_TEMP_celsius"] = nullptr;
  //wthr_data["bmp280_TEMP_celsius"] = nullptr;
  //wthr_data["PARTICLES_ugm3"] = nullptr;


  serializeJson(wthr_data,serial_json);
  serializeJsonPretty(wthr_data,Serial);
}

void printDriverError( CCS811Core::status errorCode )
{
  switch ( errorCode )
  {
    case CCS811Core::SENSOR_SUCCESS:
      Serial.print("SUCCESS");
      break;
    case CCS811Core::SENSOR_ID_ERROR:
      Serial.print("ID_ERROR");
      break;
    case CCS811Core::SENSOR_I2C_ERROR:
      Serial.print("I2C_ERROR");
      break;
    case CCS811Core::SENSOR_INTERNAL_ERROR:
      Serial.print("INTERNAL_ERROR");
      break;
    case CCS811Core::SENSOR_GENERIC_ERROR:
      Serial.print("GENERIC_ERROR");
      break;
    default:
      Serial.print("Unspecified error.");
  }
}

void loop()
{
  //Read sensor data ----------------------------
  if (myCCS811.dataAvailable()) //Check to see if CCS811 has new data (it's the slowest sensor)
  {
    myCCS811.readAlgorithmResults(); //Read latest from CCS811 and update tVOC and CO2 variables
    cacheData();
    myCCS811.setEnvironmentalData(myBME280.readFloatHumidity(), myBME280.readTempC()+temp_offset); //calibrate co2 and tvoc readings using humidity and temp data from BME
  }
  else if (myCCS811.checkForStatusError())
  {
    Serial.println(myCCS811.getErrorRegister());
  }

  //Update realtime db ----------------------------
  HTTPClient http;
  WiFiClientSecure client;
  client.setInsecure();

  String url_str = String (supabaseUrl) + "/" + String(realtime_table) + "?id=eq." + String(id_rt);

  http.begin(client, url_str);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("apikey", supabaseKey);
  http.addHeader("Authorization", bearer_key);
  String payload = serial_json;
  //debug payload
  Serial.println(payload);

  int httpResponseCode = http.sendRequest("PATCH",payload);

  // check if the request was successful
  if (httpResponseCode > 0) {
    Serial.printf("HTTP response code: %d\n", httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.println("Error sending PUT request");
    Serial.printf("HTTP response code: %d\n", httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  }

  //check if you need to update archive db
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= interval) {
    String url_str = String(supabaseUrl) + "/" + String(arch_table);
    http.begin(client, url_str);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", supabaseKey);
    http.addHeader("Authorization", bearer_key);
    String payload = serial_json;

    int httpResponseCode = http.sendRequest("POST",payload);

    // check if the request was successful
    if (httpResponseCode > 0) {
      Serial.printf("HTTP response code: %d\n", httpResponseCode);
      String response = http.getString();
      Serial.println(response);
    } else {
    Serial.println("Error sending PUT request");
    }

    previousTime = currentTime;
  } 

  // disconnect from the server
  http.end();

  delay(8000);
}

