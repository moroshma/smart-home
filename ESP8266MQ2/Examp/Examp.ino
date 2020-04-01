
//--------------------------------------------------------------------------
void setup() {

  Serial.begin(115200);
  Serial.println("MQ-2 Test");
  pinMode(A0, INPUT);
  pinMode(D7, INPUT);
}
//-----------------------------------------------------------------------
void loop() {
  
  Serial.print("A0 = " + String(analogRead(A0)));
  Serial.println("  D7 = " + String(digitalRead(D7)));
  delay(500);
}



