#include <LiquidCrystal.h>

// *******************************
// initialize the Libs with the
// numbers of the interface pins.
// *******************************
LiquidCrystal lcd(12, 10, 9, 8, 7, 6);


int redPin = 3;
int greenPin = 5;
int bluePin = 11;

void setup() {
  Serial.begin(9600);
  
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
  float vwc = readVH400(A0); 
  String prefix = "VWC: ";
  String out = prefix + vwc;
  
  Serial.println(out);
  lcd.setCursor(0, 1);
  lcd.print("Test...");
  
  delay(600);

  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
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
