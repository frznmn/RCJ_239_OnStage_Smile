int numRec = 8;
int tagRec = 8;
bool walking = 0;
bool flag = false;
uint32_t myTimer2 = millis();
uint32_t myTimerPlatform = millis();
uint32_t myTimer = millis(), timerVel = millis(), myTimerPov = millis();

int t = millis();

#include <Motors.h>

Motors feet = Motors(9, 8, 44); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorA = Motors(10, 23, 22, 0, 31); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(11, 25, 24, 1, 33);
Motors motorC = Motors(12, 27, 26, 2, 35);
Motors motorD = Motors(13, 29, 28, 3, 37);



float K_PROP = 2;
// #define K_PROP 2.0

int16_t Aspeed;
int16_t Bspeed;
int16_t Cspeed;
int16_t Dspeed;

int vel(int16_t spd, uint8_t encNumb)
{
  int err = ((millis() - timerVel) * 0.001 * (spd)) - nMotorEncoder[encNumb];
  return err * K_PROP;
}



void mecmove(float des_angle, float des_vel)
{
  static float des_angle_old = 0;

  if (des_angle_old != des_angle)
  {
    nMotorEncoder[0] = nMotorEncoder[1] = nMotorEncoder[2] = nMotorEncoder[3] = 0;
    timerVel = millis();
    des_angle_old = des_angle;
  }

  float rad_des_angle = radians(des_angle);                         //deg to rad convertion

  Bspeed =  des_vel * sin(rad_des_angle + M_PI_4);    //calculation of voltage multiplier for each mecanum wheel
  Aspeed = des_vel * cos(rad_des_angle + M_PI_4);
  Dspeed = des_vel * cos(rad_des_angle + M_PI_4);
  Cspeed = des_vel * sin(rad_des_angle + M_PI_4);


  /* motorA.set( -1 * Aspeed);
    motorB.set(  Bspeed);
    motorC.set(  -1 * Cspeed);
    motorD.set(  Dspeed);*/

  motorA.set( vel(-1 * Aspeed , 0));
  motorB.set( vel( Bspeed , 1));
  motorC.set( vel(-1 * Cspeed , 2));
  motorD.set( vel( Dspeed , 3));
}//едет првильно прямо!!!


void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial2.begin(9600);
}

int num = Serial3.read();

void loop()
{
  if (Serial3.available() > 0)
  {
    int8_t tag = Serial3.read();
    if (tag >= -1 && tag < 2)
    {
      Serial.println(tag);
    }
  }
}
