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

int16_t Aspeed;
int16_t Bspeed;
int16_t Cspeed;
int16_t Dspeed;

int tagRec = 8;
bool walking = 0;
uint32_t myTimer2 = millis();
uint32_t myTimerPlatform = millis();
uint32_t myTimer = millis(), timerVel = millis(), timerCond = millis();

bool best_flag = false;

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
  delay(500);
  mecmove(90, 100);
  delay(7000);
  motorA.stop();
  motorB.stop();
  motorC.stop();
  motorD.stop();
  delay(1000);
  /* mecmove(0,100);
    delay(1000);
    mecmove(270,0);
    delay(500);csfv
    mecmove(0,50);
    delay(1000);
    mecmove(270,0);
    delay(2000);
  */
}


void retreat()
{
  delay(500);
  //mecmove(270, 100);
  delay(7000);
  motorA.stop();
  motorB.stop();
  motorC.stop();
  motorD.stop();
  while (1)
  {
    delay(10);
  }
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


  motorA.set( -1 * Aspeed);
  motorB.set(  Bspeed);
  motorC.set(  -1 * Cspeed);
  motorD.set(  Dspeed);

  /* motorA.set( vel( Aspeed , 0));
    motorB.set( vel( Bspeed , 1));
    motorC.set( vel(-1 * Cspeed , 2));
    motorD.set( vel(-1 * Dspeed , 3));*/
}//




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
      best_flag = true;
      //Serial.println(Serial3.read());
    }


  }
  if (best_flag == true)
  {
    delay(70000);
    retreat();
  }



  /*  if (Serial2.available() > 0)
    {
    if (Serial2.peek() == 100)
    {
      Serial2.read();
      feet.set(200);
      //mecmove((i < 360 ? i : 0), 120);//*/

  /*int condition = 1;
    switch (condition)
    {

    case 1:
                                  //'право' - лево
      mecmove(0, 100);
      //Serial.println("Here");
      timerCond = millis();
      condition = 2;
      //mecmove(0,0);
      break;
    case 2:
      // eyepupilLeft.write(90);
      //   eyepupilRight.write(90);
      if (millis() - timerCond > 115000)
      {
        mecmove(0, 0);
        condition++;
      }
      break;
    case 3:
      mecmove(90, 200);           //прямо
      timerCond = millis();
      condition++;
      break;
    case 4:
      if (millis() - timerCond > 15000) {
        mecmove(0, 0);
        condition++;
      }
      break;
    case 5:                           //'право' - лево
      mecmove(0, 200);
      timerCond = millis();
      condition++;
      break;
    case 6:
      if (millis() - timerCond > 13000) {
        mecmove(0, 0);
        condition++;
      }
      break;


    }

  */
}
