#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini myDFPlayer;

#include <Servo.h>

#define CLOSE_LEFT_EYE 60
#define CLOSE_RIGHT_EYE 0
#define CLOSE_LEFT_PUPIL 60
#define CLOSE_RIGHT_PUPIL 0
#define DELTA_EYE 60

Servo eyelidLeft;
Servo eyelidRight;
Servo eyepupilLeft;
Servo eyepupilRight;

uint32_t   myTimerEyeLeft = millis();        //Обнуляем таймер
uint32_t   myTimerEyeRight = millis();
uint32_t   myTimerPupilLeft = millis();
uint32_t   myTimerPupilRight = millis();
uint32_t   timerCond = millis();

int condition = -1, conditionRec = -1;
int tagReal = 0, tagShowed = 0;

void setup()
{
  Serial.begin(9600);         //инициализируем UART USB
  Serial1.begin(9600);        //инициализируем UART связи со светом
  Serial2.begin(9600);        //инициализируем UART связи с платформой
  Serial3.begin(9600);        //инициализируем UART связи с плеером
  Serial.print("\tПривет!\n");
  myDFPlayer.begin(Serial3);  //инициализируем плеер
  myDFPlayer.volume(25);      //от 10 до 30

  eyelidLeft.attach(12);      //инициализируем сервопривод левых век 12
  eyelidRight.attach(11);     //инициализируем сервопривод правых век 11

  eyepupilLeft.attach(8);      //инициализируем сервопривод левой брови 8
  eyepupilRight.attach(9);     //инициализируем сервопривод правой брови 9

  myTimerEyeLeft = millis();  //Обнуляем таймер
  myTimerEyeRight = millis();
  myTimerPupilLeft = millis();
  myTimerPupilRight = millis();
  timerCond = millis();     //Обнуляем таймер
  pupilLeft(20);
  pupilRight(0);
  //condition = 2;
  pinMode(13, 1);
  delay(2000);
  myDFPlayer.play(1);
  delay(3000);
  myDFPlayer.play(2);
  delay(4000);
}

void eyeLeft(int desiredPosition)
{
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  eyelidLeft.write(CLOSE_LEFT_EYE - currentPosition);
}

void eyeRight(int desiredPosition)
{
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  eyelidRight.write(CLOSE_RIGHT_EYE + currentPosition);
}
//
void pupilLeft(int desiredPosition)
{
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  eyepupilLeft.write(CLOSE_LEFT_PUPIL - currentPosition);
}
void pupilRight(int desiredPosition)
{
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  eyepupilRight.write(CLOSE_RIGHT_PUPIL - currentPosition);
}

void loop()
{
  if (millis() - myTimerEyeLeft > 20)   //плавное движение серв
  {
    myTimerEyeLeft = millis();
    if (millis() % 4000 > 2000)
      eyeLeft(40);
    else if (millis() % 4000 > 500)
      eyeLeft(0);
  }

  if (millis() - myTimerEyeRight > 20)   //плавное движение серв
  {
    myTimerEyeRight = millis();
    if (millis() % 4000 > 2000)
      eyeRight(40);
    else if (millis() % 4000 > 500)
      eyeRight(0);
  }

  if (Serial2.available() > 0) {
    Serial1.write(Serial2.read());
    condition = Serial2.read();
    Serial.println(condition);
    switch (condition) {
      case 3:
        Serial.println("case 2");
        myDFPlayer.play(3);
        delay(9000);
        myDFPlayer.play(4);
        delay(10000);
        break;
      case 4:
        Serial.println("case 3");
        myDFPlayer.play(5);
        delay(3000);
        myDFPlayer.play(6);
        delay(8000);
        break;
    }
  }
}

/*
   myDFPlayer.next();  //Play next mp3
   myDFPlayer.previous();  //Play previous mp3
   myDFPlayer.play(1);  //Play the first mp3
   myDFPlayer.loop(1);  //Loop the first mp3
   myDFPlayer.pause();  //pause the mp3
   myDFPlayer.start();  //start the mp3 from the pause
   myDFPlayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
   myDFPlayer.enableLoopAll(); //loop all mp3 files.
   myDFPlayer.disableLoopAll(); //stop loop all mp3 files.
   myDFPlayer.playMp3Folder(4); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
   myDFPlayer.advertise(3); //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
   myDFPlayer.stopAdvertise(); //stop advertise
   myDFPlayer.playLargeFolder(2, 999); //play specific mp3 in SD:/02/004.mp3; Folder Name(1~10); File Name(1~1000)
   myDFPlayer.loopFolder(5); //loop all mp3 files in folder SD:/05.
   myDFPlayer.randomAll(); //Random play all the mp3.
   myDFPlayer.enableLoop(); //enable loop.
   myDFPlayer.disableLoop(); //disable loop.
*/
