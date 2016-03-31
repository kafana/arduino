#include <LiquidCrystal.h>

// DEFAULT: the default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts (on 3.3V Arduino boards)
// INTERNAL: an built-in reference, equal to 1.1 volts on the ATmega168 or ATmega328 and 2.56 volts on the ATmega8 (not available on the Arduino Mega)
// INTERNAL1V1: a built-in 1.1V reference (Arduino Mega only)
// INTERNAL2V56: a built-in 2.56V reference (Arduino Mega only)
// EXTERNAL: the voltage applied to the AREF pin (0 to 5V only) is used as the reference. 

#define VH400_DEFAULT_VREF DEFAULT
#define VH400_VREF 5.0

// *******************************
// initialize the Libs with the
// numbers of the interface pins.
// *******************************
LiquidCrystal lcd(12, 10, 9, 8, 7, 6);

int redPin = 3;
int greenPin = 11;
int bluePin = 5;

void setup() {
  Serial.begin(9600);

  analogReference(VH400_DEFAULT_VREF);

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Initializing...");
  lcd.setCursor(0, 1);
  lcd.print("Test...");

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

void loop() {
  float vwc = readVH400(A0, VH400_VREF);
  String prefix = "VWC: ";
  String out = prefix + vwc;
  Serial.println(out);

  if (vwc <= 0) {
    setColor(255, 255, 255);  // white
  } else if (vwc > 0 && vwc <= 10.0) {
    setColor(255, 0, 0);  // red
  } else if (vwc > 10.0 && vwc <= 15.0) {
    setColor(0, 255, 0);  // green
  } else if (vwc > 15.0 && vwc <= 39.86) {
    setColor(0, 255, 255);  // cyan
  } else {
    setColor(0, 0, 255);  // blue
  }
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Measuring...");
  
  lcd.setCursor(0, 1);
  lcd.print(out);

  delay(1000);
}

void setColor(int red, int green, int blue) {
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
