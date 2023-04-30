#include <Motors.h>


Motors feet = Motors(9, 8, 44); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorA = Motors(10, 23, 22, 0, 31); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(11, 25, 24, 1, 33); //изменены direction pin. Изначально: 50-53
Motors motorC = Motors(12, 27, 26, 2, 35);
Motors motorD = Motors(13, 29, 28, 3, 37);

bool direct = true;
int i = 0;
float K_PROP = 0.7;
uint32_t myTimer = millis(), myTimer2 = millis();

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
  float posit  = 0;
  posit = OpenMV();
  Serial.println(posit);
  if ( posit > 3.00)
  {
    motorA.stop();
    motorB.stop();
    motorC.stop();
    motorD.stop();
    while ( posit > 3.00) {
      mecmove(0, 20); // degres, speed
      posit = OpenMV();
      Serial.println("vbhj");
    }
  }
  else
  {
    while (posit <= 3) {
      mecmove(270, 0); // degres, speed
      posit = OpenMV();
    }
    motorA.stop();
    motorB.stop();
    motorC.stop();
    motorD.stop();
  }

}
int vel(int16_t spd, uint8_t encNumb)
{
  int err = ((millis() - myTimer2) * 0.001 * (spd)) - nMotorEncoder[encNumb];
  return err * K_PROP;
}
