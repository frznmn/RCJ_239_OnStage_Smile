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

/*////////////////////////////////////////////////////////////////////////////////////////
      A___0___B
      |       |
    90|       |270
      |_______|
      C  180  D
  /*/
