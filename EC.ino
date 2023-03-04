#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h> // insert this library 
#include <BlynkSimpleShieldEsp8266.h>
#include <EEPROM.h>
#include "GravityTDS.h"

#define TdsSensorPin A1
GravityTDS gravityTds;

char auth[] = "eOGuhBSc527iivvG9LWawookXl6irxoX";
char ssid[] = "LAPTOP-0N2B010N 3481";
char pass[] = "123456789";

#define EspSerial Serial3
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);

float temperature = 25, tdsValue = 0;

void setup()
{
  Serial.begin(115200);
  Serial3.begin(115200);

  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Serial.begin(115200);
  Serial.println("Micro Project Thailand ~^.^~ ");
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);      //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024); //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();           //initialization

  Blynk.begin(auth, wifi, ssid, pass, "blynk.en-26.com", 9600);   //Local server
}


int count_c = 0;

void loop()
{
  Blynk.run();
  if ( Serial3.available() )   {
    Serial.write( Serial3.read() );
  }
  if ( Serial.available() )       {
    Serial3.write( Serial.read() );
  }
  //temperature = readTemperature();  //add your temperature sensor and read it
  gravityTds.setTemperature(temperature); // set the temperature and execute temperature compensation
  gravityTds.update();                    //sample and calculate
  tdsValue = gravityTds.getTdsValue();    // then get the value
  Serial.print(tdsValue, 0);
  Serial.println("ppm");


  if (tdsValue >= 200) {
    count_c++;
    Serial.print("count_c : "); Serial.println(count_c);
  }
  else if (tdsValue < 200) {
  }

  delay(1000);
  Blynk.virtualWrite(V2, tdsValue);
}
