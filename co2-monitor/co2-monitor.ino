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
#include <Wire.h>
#include <LiquidCrystal.h>
#include "cozir.h"

#define REDLITE 3
#define GREENLITE 5
#define BLUELITE 6

#define LCD_BRIGHTNESS 192 /* Overall brightness by range 0 - 255 */

byte degree[8] = {
  0xc,0x12,0x12,0xc,0x0,0x0,0x0
};

byte co2_c[8] = {
  0xe,0x1b,0x18,0x18,0x18,0x1b,0xe
};

byte co2_o[8] = {
  0xe,0x1b,0x1b,0x1b,0x1b,0x1b,0xe
};

byte co2_2[8] = {
  0x0,0x0,0xc,0x12,0x4,0x8,0x1e
};

// *******************************
// initialize the Libs with the
// numbers of the interface pins.
// *******************************
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

SoftwareSerial sws(2, 4); // RX, TX
// *******************************

COZIR czr(&sws);

void setup()
{
  Serial.begin(9600);
  delay(500);

  Serial.print("Cozir SoftwareSerial: ");
  Serial.println(COZIR_LIB_VERSION);
  Serial.println();
  
  sws.begin(9600);
  czr.init();

  pinMode(REDLITE, OUTPUT);
  pinMode(GREENLITE, OUTPUT);
  pinMode(BLUELITE, OUTPUT);

  // *******************************
  // Set up the LCD
  // *******************************
  lcd.createChar(0, degree);
  lcd.createChar(1, co2_c);
  lcd.createChar(2, co2_o);
  lcd.createChar(3, co2_2);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Initializing...");
  lcd.setCursor(0, 1);
  lcd.print("Cozir v");
  lcd.print(COZIR_LIB_VERSION);
  // *******************************

  // *******************************
  // Probe LCD colors (R & G)
  // *******************************
  for (int i = 0; i < 255; i+=1) {
    setBacklight(i, 255-i, 0);
    delay(5);
  }
  for (int i = 0; i < 255; i+=1) {
    setBacklight(255-i, i, 0);
    delay(5);
  }
  // *******************************
}

void loop()
{
  uint32_t c = czr.CO2();
  float t = czr.Celsius();
  float f = czr.Fahrenheit();
  float h = czr.Humidity();

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
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write((uint8_t)1);
  lcd.write((uint8_t)2);
  lcd.write((uint8_t)3);
  lcd.print(" ");
  lcd.print(c);
  lcd.print("ppm");

  lcd.setCursor(0, 1);
  lcd.print(f);
  lcd.write((uint8_t)0);
  lcd.write("F");
  lcd.print(" ");
  lcd.print(h);
  lcd.print("%");

  if (c > 300 && c <= 450) {
    setBacklight(0, 255, 0);
  } else if (c > 450 && c <= 500) {
    setBacklight(16, 240, 0);
  } else if (c > 500 && c <= 650) {
    setBacklight(32, 224, 0);
  } else if (c > 650 && c <= 750) {
    setBacklight(48, 208, 0);
  } else if (c > 750 && c <= 850) {
    setBacklight(64, 192, 0);
  } else if (c > 850 && c <= 950) {
    setBacklight(80, 176, 0);
  } else if (c > 950 && c <= 1100) {
    setBacklight(96, 160, 0);
  } else if (c > 1100 && c <= 1200) {
    setBacklight(112, 144, 0);
  } else if (c > 1200 && c <= 1300) {
    setBacklight(128, 128, 0);
  } else if (c > 1300 && c <= 1400) {
    setBacklight(144, 112, 0);
  } else if (c > 1400 && c <= 1500) {
    setBacklight(160, 96, 0);
  } else if (c > 1500 && c <= 1600) {
    setBacklight(176, 80, 0);
  } else if (c > 1600 && c <= 1700) {
    setBacklight(192, 64, 0);
  } else if (c > 1700 && c <= 1800) {
    setBacklight(208, 48, 0);
  } else if (c > 1800 && c <= 1900) {
    setBacklight(224, 32, 0);
  } else if (c > 1900 && c <= 2000) {
    setBacklight(240, 16, 0);
  } else if (c > 2000) {
    setBacklight(255, 0, 0);
  } else {
    setBacklight(0, 0, 255); /* Unable to read value from the co2 sensor? */
  }
}

void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
  r = map(r, 0, 255, 0, 128); /* Adafruit RGB: normalize the red LED - its brighter than the rest! */
  g = map(g, 0, 255, 0, 128); /* Reduce green to half */

  r = map(r, 0, 255, 0, LCD_BRIGHTNESS);
  g = map(g, 0, 255, 0, LCD_BRIGHTNESS);
  b = map(b, 0, 255, 0, LCD_BRIGHTNESS);

  // common anode so invert!
  r = map(r, 0, 255, 255, 0);
  g = map(g, 0, 255, 255, 0);
  b = map(b, 0, 255, 255, 0);
  
  analogWrite(REDLITE, r);
  analogWrite(GREENLITE, g);
  analogWrite(BLUELITE, b);
}

