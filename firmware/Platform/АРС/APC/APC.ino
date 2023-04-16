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
  Serial1.begin(9600);
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
  while (Serial1.available() > 0)
  {
    char apc = Serial1.read();
    Serial.println(apc);
    while (apc == '2') {
      mecmove(90, 250); //tyhtf
      apc = Serial1.read();
    }
    if (apc == '3') {
      mecmove(180, 250);//
      apc = Serial1.read();
    }
    if (apc == '4') {
      mecmove(270, 250);
      apc = Serial1.read();
    }
    if (apc == '5') {
      mecmove(0, 250);
      apc = Serial1.read();
    }
  }
  motorA.stop();
  motorB.stop();
  motorC.stop();
  motorD.stop();

}
