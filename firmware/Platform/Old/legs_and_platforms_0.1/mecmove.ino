int16_t Aspeed;
int16_t Bspeed;
int16_t Cspeed;
int16_t Dspeed;

void mecmove(float des_angle, float des_vel)
{
  float rad_des_angle = radians(des_angle);                         //deg to rad convertion

  Bspeed =  des_vel * sin(rad_des_angle + M_PI_4);    //calculation of voltage multiplier for each mecanum wheel
  Aspeed = des_vel * cos(rad_des_angle + M_PI_4);
  Dspeed = des_vel * cos(rad_des_angle + M_PI_4);
  Cspeed = des_vel * sin(rad_des_angle + M_PI_4);


  /* motorA.set( -1 * Aspeed);
    motorB.set(  Bspeed);
    motorC.set(  -1 * Cspeed);
    motorD.set(  Dspeed);*/

  motorA.set( vel( Aspeed , 31));
  motorB.set( vel( Bspeed , 33));
  motorC.set( vel( -1*Cspeed , 35));
  motorD.set( vel(-1* Dspeed , 37));
}//

/*////////////////////////////////////////////////////////////////////////////////////////
      A___0___B
      |       |
    90|       |270
      |_______|
      C  180  D
  /*/
