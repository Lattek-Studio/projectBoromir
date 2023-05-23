#include <ArduinoJson.h>
#include <ArduinoJson.hpp>


//Sensor lib configs
#include <SparkFunCCS811.h>
#include <SparkFunBME280.h>
#include <Wire.h>
#define CCS811_ADDR 0x5B

CCS811 myCCS811(CCS811_ADDR);
BME280 myBME280;

//json for caching data
const int capacity = JSON_OBJECT_SIZE(10);
StaticJsonDocument<capacity> wthr_data;

void setup() {
  Serial.begin(9600);
  Wire.begin();

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
  wthr_data["CO2_ppm"] = myCCS811.getCO2();
  //Serial.print(myCCS811.getCO2());

  wthr_data["TVOC_ppb"] = myCCS811.getTVOC();
  //Serial.print(myCCS811.getTVOC());

  wthr_data["average_TEMP_celsius"] = myBME280.readTempC();
  //Serial.print(myBME280.readTempC(), 1);

  wthr_data["PRESSURE_pascals"] = myBME280.readFloatPressure();
  //Serial.print(myBME280.readFloatPressure(), 2);

  wthr_data["HUMIDITY_percent"] = myBME280.readFloatHumidity();
  //Serial.print(myBME280.readFloatHumidity(), 0);

  String serial_json;
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
  }
  else if (myCCS811.checkForStatusError())
  {
    Serial.println(myCCS811.getErrorRegister());
  }

  delay(2000);
}

