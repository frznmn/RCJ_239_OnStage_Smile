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
bool tag_flag = true, flag = true, flag_nach = true;
uint32_t myTimer2 = millis();
uint32_t myTimerPlatform = millis();
uint32_t myTimer = millis(), timerVel = millis(), Timer_dvizh = millis(), timerCond = millis();
int8_t angle[4] = {0, 90, 180, 270};

float K_PROP = 2;

int16_t Aspeed;
int16_t Bspeed;
int16_t Cspeed;
int16_t Dspeed;

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
  if (Serial2.available()) {
    Serial.print("Serial2: ");
    Serial.println(Serial2.read());
  }
  if (Serial3.available()) {
    Serial.print("Serial3: ");
    Serial.println(Serial3.read());
  }
  if (Serial3.available() > 0)
  {
    int tag = Serial3.read();
    //Serial.println(tag);
    if (tag == 0) {
      Serial.print("str#79 ");
      Serial.println(condition);
      condition = 1;
    }
    else if (tag == 1) {
      Serial.print("str#84 ");
      Serial.println(condition);
      //flag = true;
      condition = 2;
    }
    else if ( tag == 2) {
      Serial.print("str#89 ");
      Serial.println(condition);
      //flag = true;
      condition = 3;
    }
    else if (tag == 3) {
      Serial.print("str#94 ");
      Serial.println(condition);
      condition = 5;
    }
    Serial.println(condition);
    switch (condition)
    {
      case 1:
        Serial.println("case 1");
        while (true) {
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
        }
        break;
      case 2:
        Serial.println("case 2");
        Serial2.write(condition);                     //первый жест, отправляем на голос
        break;  
      case 3:
        Serial.println("case 3");
        Serial2.write(condition);                     //первый жест, отправляем на голос
        break;  
    }
  }
}
