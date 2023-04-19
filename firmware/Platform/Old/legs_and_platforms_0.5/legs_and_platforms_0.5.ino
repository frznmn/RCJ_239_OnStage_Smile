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

int tagRec = 8;
bool walking = 0;
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
  if (Serial3.available() > 0)
  {
    int8_t tag = Serial3.read();
    if (tag >= 0 && tag < 8)
    {
      if (Serial2.available() > 0)
      {
        tagRec = Serial2.read();
        Serial.println(tagRec);
      }

      if ( tagRec != tag)
        if (tagRec != 100)
          Serial2.write(tag);
      //Serial.println(Serial3.read());
    }

  }

  if (Serial2.available() > 0)
  {
    if (Serial2.peek() == 100)
    {
      Serial2.read();
      feet.set(200);
      Serial.println("Ыыыа");
      mecmove(0, 10);
    }
    else
    {
      feet.set(0);
    }
  }
}
