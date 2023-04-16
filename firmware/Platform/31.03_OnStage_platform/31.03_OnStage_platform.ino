#include <Motors.h>
#define speedM 70
#define melissa millis()

Motors feet = Motors(9, 8, 44); //pinPWM, pinA, pinB, interruptNumber, directionPin(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
Motors motorA = Motors(10, 23, 22, 0, 31); //pinPWM, pinA, pinB, interruptNumber, directionPin
Motors motorB = Motors(11, 25, 24, 1, 33);
Motors motorC = Motors(12, 27, 26, 2, 35);
Motors motorD = Motors(13, 29, 28, 3, 37);

int tagRec = -1;
bool walking = 0;
bool tag_flag = true;
uint32_t myTimer2 = millis();
uint32_t myTimerPlatform = millis();
uint32_t myTimer = millis(), timerVel = millis(), Timer_dvizh = millis();
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
}

void loop()
{
  if (Serial3.available() > 0)
  {
    int tag = Serial3.read();
    Serial.println(tag);
    if (tag_flag == true) {
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
      }

    }
  }
}
