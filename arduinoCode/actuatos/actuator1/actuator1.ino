#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

//network configs
const char* ssid = "OUR internet";
const char* pass = "3.6 roentgen";

//db config
// Supabase API endpoint and key
const char* supabaseUrl = "https://supaapi.byteforce.ro/rest/v1";
const char* realtime_table = "sensor_realtime";
const char* supabaseKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJzZXJ2aWNlX3JvbGUiLAogICAgImlzcyI6ICJzdXBhYmFzZS1kZW1vIiwKICAgICJpYXQiOiAxNjQxNzY5MjAwLAogICAgImV4cCI6IDE3OTk1MzU2MDAKfQ.DaYlNEoUrrEn2Ig7tqibS-PHK5vgusbcbo7X36XVt4Q";
const char* bearer_key = "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyAgCiAgICAicm9sZSI6ICJzZXJ2aWNlX3JvbGUiLAogICAgImlzcyI6ICJzdXBhYmFzZS1kZW1vIiwKICAgICJpYXQiOiAxNjQxNzY5MjAwLAogICAgImV4cCI6IDE3OTk1MzU2MDAKfQ.DaYlNEoUrrEn2Ig7tqibS-PHK5vgusbcbo7X36XVt4Q";
// the ID of the row
const char* id_rt = "2"; //1 = weather station; 2 = room sensor 

//json for caching data
const int capacity = JSON_OBJECT_SIZE(10) + 256;
StaticJsonDocument<capacity> downloaded_json;
StaticJsonDocument<capacity> modded_json;
String response;

bool fan, geam;
bool prev_state_fan, prev_state_geam, curr_state_fan, curr_state_geam;

//DC Pins
#define ENA D3
#define IN1 D4
#define IN2 D5
//Servo pin
#include <Servo.h>
#define PWM_SERVO D6

Servo myservo;

void setup() {
  Serial.begin(9600);

  //connect to wifi
  Serial.print("Connecting");
  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    
   
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Connected :D \n");

  //Setup DC
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,0);

  //Setup Servo
  myservo.attach(PWM_SERVO);
  myservo.write(0);

  const size_t capaciti = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(12) + 200;
  DynamicJsonDocument downloaded_json(capaciti);
}

void fan_on()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,255);
}
void fan_off()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,0);
}

void loop() {
  //Get values from realtime db ----------------------------
  HTTPClient http;
  WiFiClientSecure client;
  client.setInsecure();

  String url_str = String (supabaseUrl) + "/" + String(realtime_table) + "?id=eq." + String(id_rt);

  http.begin(client, url_str);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("apikey", supabaseKey);
  http.addHeader("Authorization", bearer_key);

  int httpResponseCode = http.GET();

  // check if the request was successful
  if (httpResponseCode > 0) {
    Serial.printf("HTTP response code: %d\n", httpResponseCode);
    response = http.getString();
    response = response.substring(1, response.length() - 1);
    Serial.println(response);
  } else {
    Serial.println("Error sending PUT request");
    Serial.printf("HTTP response code: %d\n", httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  }

  DeserializationError error = deserializeJson(downloaded_json, response);

  if (error) {
    Serial.print("JSON deserialization failed: ");
    Serial.println(error.c_str());
  }
  fan = downloaded_json["fan"];
  geam = downloaded_json["geam"];

  if(downloaded_json["average_TEMP_celsius"]>30)
  {
    curr_state_fan = 1;
  }
  else
  {
    curr_state_fan = 0;
  }
  if(downloaded_json["CO2_ppm"]>2000 || downloaded_json["HUMIDITY_percent"]>70)
  {
    curr_state_geam = 1;
  }
  else
  {
    curr_state_geam = 0;
  }


  if(prev_state_fan != curr_state_fan)
  {
    fan = curr_state_fan;
    prev_state_fan = fan;
  }
  

  if(prev_state_geam != curr_state_geam)
  {
    geam = curr_state_geam;
    prev_state_geam = geam;
  }

  //switch actual states
  if(fan)
  {
    fan_on();
  }
  else
  {
    fan_off();
  }

  if(geam){
    myservo.write(90);
  }
  else
  {
    myservo.write(0);
  }

  //values to return in db
  modded_json["fan"] = fan;
  modded_json["geam"] = geam;


  //set values in db to actual values
  String payload;
  serializeJson(modded_json,payload);
  serializeJsonPretty(modded_json,Serial);


  http.begin(client, url_str);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("apikey", supabaseKey);
  http.addHeader("Authorization", bearer_key);
  httpResponseCode = http.sendRequest("PATCH",payload);

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
  http.end();
  delay(500);
}