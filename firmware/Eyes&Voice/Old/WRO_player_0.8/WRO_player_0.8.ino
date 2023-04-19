#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini myDFPlayer;

#include <Servo.h>

#define CLOSE_LEFT_EYE 50
#define CLOSE_RIGHT_EYE 0
#define DELTA_EYE 50

Servo eyelidLeft;
Servo eyelidRight;

uint32_t myTimer1 = millis();
uint32_t myTimer2 = millis();
uint32_t myTimer3 = millis();
uint32_t myTimer4 = millis();

int currentPosition = 0;
int desiredPosition = 0;

int condition = 1, conditionOld = 0;

void eye()
{
  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  eyelidLeft.write(CLOSE_LEFT_EYE - currentPosition);
  eyelidRight.write(CLOSE_RIGHT_EYE + currentPosition);
}

void setup()
{
  Serial.begin(9600);         //инициализируем UART USB
  Serial1.begin(9600);        //инициализируем UART связи со светом
  Serial3.begin(9600);        //инициализируем UART связи с плеером
  myDFPlayer.begin(Serial3);  //инициализируем плеер

  eyelidLeft.attach(11);      //инициализируем сервопривод левых век
  eyelidRight.attach(10);     //инициализируем сервопривод правых век

  myTimer3 = millis();        //Обнуляем таймер
}

void loop()
{
  if (millis() - myTimer2 > 20)   //плавное движение серв
  {
    myTimer2 = millis();
    eye();
  }

  switch (condition)
  {
    case 1:
      desiredPosition = 40;
      Serial1.write(condition);
      myDFPlayer.play(6);         //Аудизапись приветствие
      condition++;
      break;
    case 2:
      if (millis() - myTimer3 > 10000)
        condition++;
      break;
    case 3:
      Serial1.write(condition);
      myDFPlayer.play(8);    //Аудизапись эмоций

      condition++;
      break;
    case 4:
      if (millis() - myTimer3 > 13000)
        condition++;
      break;
    case 5:
      Serial1.write(condition);
      myDFPlayer.play(9);         //Аудизапись улыбка

      condition++;
      break;
    case 6:
      if (millis() - myTimer3 > 16000)
        condition++;
      break;
    case 7:
      Serial1.write(condition);
      myDFPlayer.play(10);         //Аудизапись грусть
      condition++;
      break;
    case 8:
      if (millis() - myTimer3 > 19000)
        condition++;
      break;
    case 9:
      desiredPosition = 20;
      Serial1.write(condition);
      myDFPlayer.play(11);         //Аудизапись злость
      condition++;
      break;
    case 10:
      if (millis() - myTimer3 > 22000)
        condition++;
    case 11:
      desiredPosition = 50;
      Serial1.write(condition);
      myDFPlayer.play(12);         //Аудизапись удивление
      condition++;
      break;
    case 12:
      if (millis() - myTimer3 > 215000)
        condition++;
    case 13:
      desiredPosition = 40;
      Serial1.write(condition);
      myDFPlayer.play(13);         //Аудизапись финал
      condition++;
    case 14:
      if (millis() - myTimer3 > 28000) {
        myDFPlayer.pause();
        desiredPosition = 10;
        condition++;
      }
      break;
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
