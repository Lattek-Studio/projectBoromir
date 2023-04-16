#include <SparkFunBME280.h>
#include <SparkFunCCS811.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>


#include <cstring>
#include <string>
//Global sensor objects
CCS811 myCCS811(CCS811_ADDR);
BME280 myBME280;


#define WIFI_SSID "TP-Link_4988"
#define WIFI_PASSWORD "06687656"

#define API_KEY "AIzaSyAQGxZdMZAZaCtUIZ8iTPLlrE8jbfR73e4"

#define USER_EMAIL "test@lazar.lol"
#define USER_PASSWORD "lazaresmecher"

#define DATABASE_URL "sensors-82505-default-rtdb.europe-west1.firebasedatabase.app"

#define DATABASE_SECRET "5K62SME5IZViBf285bj6Dea3CqaoLgPoINqQA9io"

FirebaseData fbdo;

/* 7. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* 8. Define the FirebaseConfig data for config data */
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
void setup()
{
  Serial.begin(9600);
  Serial.println("Apply BME280 data to CCS811 for compensation.");
  Wire.begin();//initialize I2C bus
  //This begins the CCS811 sensor and prints error status of .begin()
  myCCS811.begin();
  //Initialize BME280
  //For I2C, enable the following and disable the SPI section
  myBME280.settings.commInterface = I2C_MODE;
  myBME280.settings.I2CAddress = 0x77;
  myBME280.settings.runMode = 3; //Normal mode
  myBME280.settings.tStandby = 0;
  myBME280.settings.filter = 4;
  myBME280.settings.tempOverSample = 5;
  myBME280.settings.pressOverSample = 5;
  myBME280.settings.humidOverSample = 5;
  //Calling .begin() causes the settings to be loaded
  delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
  byte id = myBME280.begin(); //Returns ID of 0x60 if successful
  if (id != 0x60)
  {
    Serial.println("Problem with BME280");
  }
  else
  {
    Serial.println("BME280 online");
  }
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL */
    config.database_url = DATABASE_URL;

    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);


    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);
    if (Firebase.getInt(fbdo, "/int" )){    
      count = (fbdo.intData());
    }
    /** Now modify the database rules (if not yet modified)
     *
     * The user, <user uid> in this case will be granted to read and write
     * at the certain location i.e. "/UsersData/<user uid>".
     *
     * If you database rules has been modified, please comment this code out.
     *
     * The character $ is to make a wildcard variable (can be any name) represents any node key
     * which located at some level in the rule structure and use as reference variable
     * in .read, .write and .validate rules
     *
     * For this case $userId represents any <user uid> node that places under UsersData node i.e.
     * /UsersData/<user uid> which <user uid> is user UID.
     *
     * Please check your the database rules to see the changes after run the below code.
     */
    // String var = "$userId";
    // String val = "($userId === auth.uid && auth.token.premium_account === true && auth.token.admin === true)";
    // Firebase.setReadWriteRules(fbdo, "/", var, val, val, DATABASE_SECRET);
    
    /** path for user data is now "/UsersData/<user uid>"
     * The user UID can be taken from auth.token.uid
     * 
     * The refresh token can be accessed from Firebase.getRefreshToken().
     */
  
  timeClient.begin();


}

void printData(){
  int co2 = myCCS811.getCO2();
  int tvoc = myCCS811.getTVOC();
  double temp = myBME280.readTempC();
  double p = myBME280.readFloatPressure();
  double h = myBME280.readFloatHumidity();

  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  FirebaseJson json;
  json.add("timestamp",epochTime);
  json.add("CO2",co2);
  json.add("TVOC",tvoc);
  json.add("humidity",h);
  json.add("pressure",p);
  json.add("temperature",temp);

  if (Firebase.setJSON(fbdo, "/storage/" + String(epochTime) + "/", json)) {
    Serial.println(fbdo.dataPath());
    Serial.println(fbdo.pushName());
    Serial.println(fbdo.dataPath() + "/"+ fbdo.pushName());
  } else {
    Serial.println(fbdo.errorReason());
  }
  if (Firebase.setJSON(fbdo, "/data/", json)) {
    Serial.println(fbdo.dataPath());
    Serial.println(fbdo.pushName());
    Serial.println(fbdo.dataPath() + "/"+ fbdo.pushName());
  } else {
    Serial.println(fbdo.errorReason());
  }

}

void loop()
{
  if (myCCS811.dataAvailable()) //Check to see if CCS811 has new data (it's the slowest sensor)
  {
    myCCS811.readAlgorithmResults(); //Read latest from CCS811 and update tVOC and CO2 variables
    //getWeather(); //Get latest humidity/pressure/temp data from BME280
    printData(); //Pretty print all the data
  }
  else if (myCCS811.checkForStatusError()) //Check to see if CCS811 has thrown an error
  {
    Serial.println(myCCS811.getErrorRegister()); //Prints whatever CSS811 error flags are detected
  }

  delay(1000); //Wait for next reading

  if (millis() - dataMillis > 1000 && Firebase.ready())
    {
        dataMillis = millis();

        
        
          Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, "/int", count++) ? "ok" : fbdo.errorReason().c_str());          
        

        // You can use refresh token from Firebase.getRefreshToken() to sign in next time without providing Email and Password.
        // See SignInWithRefreshIDToken example.
    }
}
