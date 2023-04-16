  #include <Servo.h>
#define CLOSE_LEFT_EYE 50
#define CLOSE_RIGHT_EYE 0
#define DELTA_EYE 50

Servo eyelidLeft;
Servo eyelidRight;

uint32_t myTimer1 = millis();
uint32_t myTimer2 = millis();

int currentPosition = 0;
int desiredPosition = 0;

void setup()
{
  eyelidLeft.attach(12);
  eyelidRight.attach(10);
}

void eye()
{
  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;
    
  eyelidLeft.write(CLOSE_LEFT_EYE - currentPosition);
  eyelidRight.write(CLOSE_RIGHT_EYE + currentPosition);
}

void openEye()
{
  for (; currentPosition <= DELTA_EYE; currentPosition += 1)
  {
    eyelidLeft.write(CLOSE_LEFT_EYE - currentPosition);
    eyelidRight.write(CLOSE_RIGHT_EYE + currentPosition);
    delay(20);
  }
}

void closeEye()
{
  for (; currentPosition >= 0; currentPosition -= 1)
  {
    eyelidLeft.write(CLOSE_LEFT_EYE - currentPosition);
    eyelidRight.write(CLOSE_RIGHT_EYE + currentPosition);
    delay(20);
  }
}


void loop()
{
  if (millis() - myTimer1 > 2000)
    desiredPosition = 0;
  if (millis() - myTimer1 > 4000)
  {
    myTimer1 = millis();
    desiredPosition = DELTA_EYE;
  }

  if (millis() - myTimer2 > 20)
  {
    myTimer2 = millis();
    eye();
  }

  /*closeEye();
    delay(2000);
    openEye();
    delay(2000);//*/
}

/*
   Пример. Охраняется Евгенией.
  void setup()
  {
  Serial.begin(9600);
  pinMode(13,1);
  }

  void loop()
  {
  char temp = "";
  if (Serial.available() > 0)
    temp = Serial.read();

  if(temp == "I")
    digitalWrite(13, 1);

  if(temp == "O")
    digitalWrite(13, 0);
  }*/
