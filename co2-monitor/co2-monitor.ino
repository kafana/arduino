/*
  This sketch connects will connect to a COZIR ambient sensor
  and report readings back to the host computer over usb.
     
    Arduino                 COZIR Sensor
  ================================
    GND ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐- 1 (gnd)
    3.3v‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐ 3 (Vcc)  
    10 ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐ 5 (Rx)
    11 ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐ 7 (Tx)
*/

#include <SoftwareSerial.h>
#include "cozir.h"

SoftwareSerial sws(10, 11); // RX, TX

COZIR czr(&sws);

void setup()
{
  sws.begin(9600);
  czr.init();
  
  Serial.begin(9600);
  Serial.print("Cozir SoftwareSerial: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();

  // czr.SetOperatingMode(CZR_POLLING);
  // czr.SetOperatingMode(CZR_STREAMING);
  // czr.CalibrateFreshAir();
  // czr.SetDigiFilter(64);

  delay(1000);
}

void loop()
{
  float t = czr.Celsius();
  float f = czr.Fahrenheit();
  float h = czr.Humidity();
  uint32_t c = czr.CO2();

  Serial.print("Celcius =\t");
  Serial.println(t);
 
  Serial.print("Fahrenheit =\t");
  Serial.println(f);

  Serial.print("Humidity =\t");
  Serial.println(h);

  Serial.print("CO2 =\t");
  Serial.println(c);

  Serial.println();

  delay(3000);
}

