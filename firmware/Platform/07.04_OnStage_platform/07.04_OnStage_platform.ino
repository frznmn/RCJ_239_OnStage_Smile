#include <Motors.h>
#define speedM 70
#define melissa millis()

Motors feet = Motors(9, 8, 44); //pinPWM, pinA, pinB, interruptNumber, directionPin(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
Motors motorA = Motors(10, 23, 22, 0, 31); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(11, 25, 24, 1, 33);
Motors motorC = Motors(12, 27, 26, 2, 35);
Motors motorD = Motors(13, 29, 28, 3, 37);

int tagRec = -1, condition = -1;
bool walking = 0;
bool tag_flag = true;
uint32_t myTimer2 = millis();
uint32_t myTimerPlatform = millis();
uint32_t myTimer = millis(), timerVel = millis(), Timer_dvizh = millis(), timerCond = millis();
int8_t angle[4] = {0, 90, 180, 270};

float K_PROP = 2;

int16_t Aspeed;
int16_t Bspeed;
int16_t Cspeed;
int16_t Dspeed;

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

  motorA.set( -1 * Aspeed );
  motorB.set(Bspeed );
  motorC.set(-1 * Cspeed );
  motorD.set( Dspeed );
}//едет прaвильно прямо!!!
/*
      A___0___B
      |       |
    90|       |270
      |_______|
      C  180  D
  /*/


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
  Timer_dvizh = millis();
  timerCond = millis();
}

void loop()
{
  if (Serial3.available() > 0)
  {
    int tag = Serial3.read();
    Serial.println(tag);
    if (tag == 0) {
      Serial.print("str#79 ");
      Serial.println(condition);
      condition = 1;
    }
    else if (tag == 1) {
      Serial.print("str#84 ");
      Serial.println(condition);
      condition = 2;
    }
    else if ( tag == 2) {
      condition = 3;
    }
    else if (tag == 3) {
      condition = 4;
    }
    //Serial.println(condition);
    switch (condition)
    {
      case 1:
      //Serial.println("case 1");
        if (Serial3.available() > 0)                        //движение за тегом
        {
          int8_t tag_dvizh = Serial3.read();
          if (tag_dvizh > -2 && tag_dvizh < 3) {
            Serial.println(tag_dvizh);
            if (tag_dvizh == 0) {
              while (tag_dvizh == 0) {
                feet.set(400);
                tag_dvizh = Serial3.read();
                motorA.set(-speedM);
                motorB.set(speedM);
                motorC.set(-speedM);
                motorD.set(speedM);
              }
            }
            else if (tag_dvizh == 1) {
              while (tag_dvizh == 1) {
                feet.set(400);
                tag_dvizh = Serial3.read();
                motorA.set(speedM);
                motorB.set(speedM);
                motorC.set(speedM);
                motorD.set(speedM);
              }
            }
            else if (tag_dvizh == -1) {
              while (tag_dvizh == -1) {
                feet.set(400);
                tag_dvizh = Serial3.read();
                motorA.set(-speedM);
                motorB.set(-speedM);
                motorC.set(-speedM);
                motorD.set(-speedM);
              }
            }
            else if (tag_dvizh == 2) {
              delay(50);
              tag_dvizh = Serial3.read();
              while (tag_dvizh == 2) {
                tag_dvizh = Serial3.read();
                feet.stop();
                motorA.set(0);
                motorB.set(0);
                motorC.set(0);
                motorD.set(0);
              }
            }
          }
        }
        break;//*/
     /* case 2:
        Serial.println("case 2");
        Serial2.write(condition);                       //начало, подъезжаем к роботу
        Timer_dvizh = melissa;
        while ( melissa % 20000 < 10000) {
          feet.set(400);
          Timer_dvizh = melissa;
          mecmove(315, 70);
        }
        feet.stop();
        motorA.set(0);
        motorB.set(0);
        motorC.set(0);
        motorD.set(0);
        break;
      case 3:
        Serial2.write(condition);                     //первый жест, двигаемся туда-сюда
        // if (Serial2.available() > 0) {
        // if (Serial2.read() == condition) {
        while (melissa % 6000 < 300 nbo0) {
          feet.set(400);
          mecmove(90, speedM);
        }
        feet.stop();
        motorA.set(0);
        motorB.set(0);
        motorC.set(0);
        motorD.set(0);
        delay(100);
        while (melissa % 6000 < 3000) {
          feet.set(400);
          mecmove(270, speedM);
        }
        feet.stop();
        motorA.set(0);
        motorB.set(0);
        motorC.set(0);
        motorD.set(0);
        break;
      case 4:
        Serial2.write(condition);                  //второй жест
        break;
      case 5:
        Serial2.write(condition);
        break;*/
      default: break;

    }
  }
}



/* if (tag_flag == true) {
      tag = Serial3.read();
      while ( tag != 24) {
        feet.set(280);
        mecmove(315, speedM);
      }
      feet.stop();
      mecmove(0, 0);
      Serial2.write("tag");
      tag_flag = false;
     }
     if (tag >= 0 && tag < 5) {
      if (tag == 0) {
        Serial2.write(0);
        while (melissa - Timer_dvizh < 3000) {
          mecmove(angle[1], speedM);
          Timer_dvizh = melissa;
        }

        while (melissa - Timer_dvizh < 3000) {
          mecmove(angle[2], speedM);
          Timer_dvizh = melissa;
        }
      }
      else if (tag == 1) {
        mecmove(0, 100);
        feet.set(200);
      }
      else if (tag == 2) {
        feet.stop();
        Serial2.write(tag);
      }*/
