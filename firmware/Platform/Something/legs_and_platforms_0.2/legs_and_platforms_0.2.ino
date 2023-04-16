/*
    Библиотека для управления моторами проекта Time
    v 1.5
    Разработчик Хартанен А.В.
*/

#include <Motors.h>

Motors feet = Motors(9, 8, 44); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorA = Motors(10, 23, 22, 0, 31); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(11, 25, 24, 1, 33); //изменены direction pin. Изначально: 50-53
Motors motorC = Motors(12, 27, 26, 2, 35);
Motors motorD = Motors(13, 29, 28, 3, 37);

int numRec = 8;
int cond = 0;
uint32_t myTimer2 = millis();

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial2.begin(9600);
  digitalWrite(50, 1);
  digitalWrite(51, 1);
  digitalWrite(52, 1);
  digitalWrite(53, 1);
}

void loop()
{
  if (Serial3.available() > 0 || Serial2.available() > 0)
  {
    int num = Serial3.read();
    if ((num > (-1)) && (num < 8))
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
    else
    {
      cond = Serial2.read();
      Serial2.write("OK, I recieved");
      if (cond == 21 || cond == 22)
      {
        feet.set(200);
        Serial.println("Ыыыа");
        mecmove(0, 10);
      }
      if (cond == 23)
      {
        feet.set(0);
      }
    }
  }
  /*else if (Serial2.available() > 0)
  {
    cond = Serial2.read();
    Serial2.write("OK, I recieved");
    if (cond == 21 || cond == 22)
    {
      feet.set(200);
      Serial.println("Ыыыа");
      mecmove(0, 10);
    }
    if (cond == 23)
    {
      feet.set(0);
    }
  }*/
}
