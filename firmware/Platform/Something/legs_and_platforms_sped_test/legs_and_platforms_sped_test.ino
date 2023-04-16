/*
    Библиотека для управления моторами проекта Улыайся!
    v 1.5
    Разработчик Хартанен А.В.
*/

#include <Motors.h>00000000000

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
  Serial.print("MA = ");
  Serial.print(nMotorEncoder[0]);
  Serial.print("\tMB = ");
  Serial.print(nMotorEncoder[1]); 
  Serial.print("\tMC = ");
  Serial.print(nMotorEncoder[2]); 
  Serial.print("\tMD = ");
  Serial.println(nMotorEncoder[3]); 

  motorA.set(vel())
}
