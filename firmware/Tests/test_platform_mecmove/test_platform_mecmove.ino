#include <Motors.h>
#define speedM 70

Motors feet = Motors(9, 8, 44); //pinPWM, pinA, pinB, interruptNumber, directionPin(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
Motors motorA = Motors(10, 23, 22, 0, 31); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(11, 25, 24, 1, 33);
Motors motorC = Motors(12, 27, 26, 2, 35);
Motors motorD = Motors(13, 29, 28, 3, 37);

int tagRec = 8;
bool walking = 0;
uint32_t myTimer2 = millis();
uint32_t myTimerPlatform = millis();
uint32_t myTimer = millis(), timerVel = millis(), Timer_dvizh = millis();

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
  mecmove(0, 70);
}
