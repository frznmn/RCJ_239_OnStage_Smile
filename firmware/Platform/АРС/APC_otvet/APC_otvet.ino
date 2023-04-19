void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  char apc;
  while ( digitalRead(2) == 0) {
    apc = '2';
    Serial.println(apc);
  }
  while ( digitalRead(3) == 0) {
    apc = '3';
    Serial.println(apc);
  }
  while ( digitalRead(4) == 0) {
    apc = '4';
    Serial.println(apc);
  }
  while ( digitalRead(5) == 0) {
    apc = '5';
    Serial.println(apc);
  }

}
