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
uint32_t myTimerPlatform = millis();
uint32_t myTimer = millis(), timerVel = millis();

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial2.begin(9600);
  digitalWrite(50, 1);
  digitalWrite(51, 1);
  digitalWrite(52, 1);
  digitalWrite(53, 1);
  nMotorEncoder[0] = nMotorEncoder[1] = nMotorEncoder[2] = nMotorEncoder[3] = 0;
  timerVel = millis();
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
      for (int i = 0; i < 360; )
      {
        mecmove((i < 360 ? i : 0), 120);
        if (millis() - myTimer > 2000)
        {
          i += 90;
          myTimer = millis();
        }
      }
    }
    else
    {
      feet.stop();
      mecmove(0, 0,0);
      delay(4000);
      
      motorA.stop();
      motorB.stop();
      motorC.stop();
      motorD.stop();
    }
  }
}
