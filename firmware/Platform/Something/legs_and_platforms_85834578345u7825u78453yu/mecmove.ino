float K_PROP = 2;
//#define K_PROP 2.0



int vel(int16_t spd, uint8_t encNumb)
{
  int err = ((millis() - timerVel) * 0.001 * (spd)) - nMotorEncoder[encNumb];
  return err * K_PROP;
}




/*////////////////////////////////////////////////////////////////////////////////////////
      A___0___B
      |       |
    90|       |270
      |_______|
      C  180  D
  /*/
