int OpenMV()
{
  float posit;
  if (Serial3.available() > 0)
  {
    int num = Serial3.read();
    /*if (num & 128)
      {
      num &= 127;
      num = (num-13)*15;
      //float posit;
      posit = num / 100.0;
      }
      else
      {
      num = (num-13)*15;
      float angle;
      angle = num / 100.0;
      }
      }*/
    return num;
  }
