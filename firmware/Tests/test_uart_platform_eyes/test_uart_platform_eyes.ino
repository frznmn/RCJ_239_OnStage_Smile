void setup() {
  Serial2.begin(9600);
  Serial.begin(9600);
}
void loop() {
  Serial2.write(24);
  if (Serial2.available()) {
    Serial.println(Serial2.read());
  }
}
