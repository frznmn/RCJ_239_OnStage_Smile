/*
 *	Библиотека для управления моторами проекта Time
 *	v 1.5
 *	Разработчик Хартанен А.В.
 */

#include <Motors.h>

Motors motorA = Motors(10, 23, 22, 0, 50); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(11, 25, 24, 1, 51);
Motors motorC = Motors(12, 27, 26, 2, 52);
Motors motorD = Motors(13, 29, 28, 3, 53);

bool direct = true;
int i = 0;
uint32_t myTimer = millis();

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (direct)
    i++;
  else
    i--;

  if (i >= 255)
    direct = false;

  if (i <= -255)
    direct = true;

  motorA.set(i);
  motorB.set(i);
  motorC.set(i);
  motorD.set(i);
  
  if(millis() - myTimer > 500)
  {
    Serial.print("nMotorEncoder[0] = ");
    Serial.print(nMotorEncoder[0]);
    Serial.print("  nMotorEncoder[1] = ");
    Serial.println(nMotorEncoder[1]);
	Serial.print("nMotorEncoder[2] = ");
    Serial.print(nMotorEncoder[2]);
    Serial.print("  nMotorEncoder[3] = ");
    Serial.print(nMotorEncoder[3]);
	Serial.print("\t");
    myTimer = millis();
  }
  delay(10);
}
