#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

//network configs
const char* ssid = "500102 2.4g";
const char* pass = "galati1923";

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

  // disconnect from the server
  http.end();

  DeserializationError error = deserializeJson(downloaded_json, response);

  if (error) {
    Serial.print("JSON deserialization failed: ");
    Serial.println(error.c_str());
  }
  fan = downloaded_json["fan"];
  geam = downloaded_json["geam"];

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

  Serial.println(fan);
  Serial.println(geam);

  delay(8000);
}