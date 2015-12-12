void setup() {
  Serial.begin(9600);
}

void loop() {
  float vwc = readVH400(A0); 
  String prefix = "VWC: ";
  String out = prefix + vwc;
  
  Serial.println(out);

  delay(350);
}
