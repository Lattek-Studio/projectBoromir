#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <GP2YDustSensor.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>



#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define DHTPIN D5

#define DHTTYPE    DHT22 
  
const uint8_t SHARP_LED_PIN = D6;   // Sharp Dust/particle sensor Led Pin
const uint8_t SHARP_VO_PIN = A0;    // Sharp Dust/particle analog out pin used for reading 

DHT_Unified dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;
GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, SHARP_LED_PIN, SHARP_VO_PIN);

const int capacity = JSON_OBJECT_SIZE(10);
StaticJsonDocument<capacity> wthr_data;

//wifi consts
const char* ssid = "CNVA2";
const char* pass = "987654321";
//const char* ssid = "OUR internet";
//const char* pass = "3.6 roentgen";

// Supabase API endpoint and key
const char* supabaseUrl = "https://supaapi.byteforce.ro/rest/v1";
const char* realtime_table = "sensor_realtime";
const char* arch_table = "sensor_arch";
const char* supabaseKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJzZXJ2aWNlX3JvbGUiLAogICAgImlzcyI6ICJzdXBhYmFzZS1kZW1vIiwKICAgICJpYXQiOiAxNjQxNzY5MjAwLAogICAgImV4cCI6IDE3OTk1MzU2MDAKfQ.DaYlNEoUrrEn2Ig7tqibS-PHK5vgusbcbo7X36XVt4Q";
const char* bearer_key = "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJzZXJ2aWNlX3JvbGUiLAogICAgImlzcyI6ICJzdXBhYmFzZS1kZW1vIiwKICAgICJpYXQiOiAxNjQxNzY5MjAwLAogICAgImV4cCI6IDE3OTk1MzU2MDAKfQ.DaYlNEoUrrEn2Ig7tqibS-PHK5vgusbcbo7X36XVt4Q";
// the ID of the row
const char* id_rt = "1";

//timer for archive
unsigned long previousTime = 0;
unsigned long interval = 120000;

float temp_offset_dht=-3; //TODO
float temp_offset_bmp=-2.3; //TODO


float bmp_temp;


void setup() {
  Serial.begin(9600);
  pinMode(D7,OUTPUT);
  digitalWrite(D7,HIGH);
  //connect to wifi
  Serial.print("Connecting");
  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    
   
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Connected :D \n");

  unsigned status;
    status = bmp.begin(0x76);
    if (!status) {
      Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                        "try a different address!"));
      Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
      Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
      Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
      Serial.print("        ID of 0x60 represents a BME 280.\n");
      Serial.print("        ID of 0x61 represents a BME 680.\n");
    }
    /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */



  dht.begin();
  sensor_t sensor;

  dustSensor.setBaseline(0.56); // set no dust voltage TODO
  //dustSensor.setCalibrationFactor(1.1); // calibrate against precision instrument

  dustSensor.begin();
}

void loop() {

    sensors_event_t event;

    wthr_data["PARTICLES_ugm3"] = dustSensor.getDustDensity(20);

    // DHT
    dht.temperature().getEvent(&event);
    wthr_data["dht_TEMP_celsius"] = event.temperature+temp_offset_dht;
    dht.humidity().getEvent(&event);
    if(event.relative_humidity<=100)
    {
      wthr_data["HUMIDITY_percent"] = event.relative_humidity+10;
    }
    else
    {
      wthr_data["HUMIDITY_percent"] =100;
    }

    if(bmp.readTemperature()>80.0)
    {
      bmp_temp = (float)wthr_data["dht_TEMP_celsius"];
      wthr_data["PRESSURE_pascals"] = nullptr;
    } 
    else
    {
      bmp_temp = bmp.readTemperature()+temp_offset_bmp;
      wthr_data["PRESSURE_pascals"] = bmp.readPressure()+250;
    }
    wthr_data["bmp280_TEMP_celsius"] = bmp_temp;
    wthr_data["average_TEMP_celsius"] = (bmp_temp+(float)wthr_data["dht_TEMP_celsius"])/2;

    String serial_json;
    serializeJson(wthr_data,serial_json);
    serializeJsonPretty(wthr_data,Serial);

    Serial.print(analogRead(A0));

    //update realtime db
    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure();

    String url_str = String (supabaseUrl) + "/" + String(realtime_table) + "?id=eq." + String(id_rt);

    http.begin(client, url_str);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", supabaseKey);
    http.addHeader("Authorization", bearer_key);
    String payload = serial_json;

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

    digitalWrite(D7,LOW);
    Serial.println("BMP Off:");
    Serial.println(bmp.readTemperature());

    delay(20000);  ///TODO
    digitalWrite(D7,HIGH);
    bmp.begin(0x76);
    delay(8000);
}