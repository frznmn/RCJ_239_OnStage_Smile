int numRec = 8;

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial2.begin(9600);
}

void loop()
{
  if (Serial3.available() > 0)
  {
    int num = Serial3.read();
    if (num == 6)
    {
      Serial.println(num);
      if (Serial2.available() > 0)
      {
        numRec = Serial2.read();
      }

      if ( numRec != num)
        Serial2.write(num);
      //Serial.println(Serial3.read());
    }

  }
}
