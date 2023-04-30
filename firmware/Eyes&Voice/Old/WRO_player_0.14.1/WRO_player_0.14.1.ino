#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini myDFPlayer;

#include <Servo.h>

#define CLOSE_LEFT_EYE 80
#define CLOSE_RIGHT_EYE 0
#define DELTA_EYE 80

Servo eyelidLeft;
Servo eyelidRight;
Servo eyepupilLeft;
Servo eyepupilRight;

uint32_t   myTimerEyeLeft = millis();        //Обнуляем таймер
uint32_t   myTimerEyeRight = millis();
uint32_t   myTimerCond = millis();

int condition = 1, conditionOld = 0, conditionRec = 0;
int num = 0;
bool flag = 0;

void setup()
{
  Serial.begin(9600);         //инициализируем UART USB
  Serial1.begin(9600);
  Serial2.begin(9600);    //инициализируем UART связи со светом
  Serial3.begin(9600);        //инициализируем UART связи с плеером
  myDFPlayer.begin(Serial3);  //инициализируем плеер
  myDFPlayer.volume(15);

  eyelidLeft.attach(12);      //инициализируем сервопривод левых век
  eyelidRight.attach(11);     //инициализируем сервопривод правых век

  myTimerEyeLeft = millis();        //Обнуляем таймер
  myTimerEyeRight = millis();
  myTimerCond = millis();        //Обнуляем таймер

  pinMode(13, 1);
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

void loop()
{
  (millis() % 200 > 100) ? digitalWrite(13, 1) : digitalWrite(13, 0); //пример короткой записи if/else

  Serial.println();

  if (millis() - myTimerEyeLeft > 20)   //плавное движение серв
  {
    myTimerEyeLeft = millis();
    if (millis() % 4000 > 3000)
      eyeLeft(40);
    else if (millis() % 4000 > 1000)
      eyeLeft(0);
  }

  if (millis() - myTimerEyeRight > 20)   //плавное движение серв
  {
    myTimerEyeRight = millis();
    if (millis() % 4000 > 3000)
      eyeRight(40);
    else if (millis() % 4000 > 1000)
      eyeRight(0);
  }

  if (Serial2.available() > 0)
  {
    flag = 1;
  }
  if (flag == 1)
  {
    if (Serial2.available() > 0)
    {
      int num = Serial2.read();
      Serial.println(num);
      Serial2.write(num);
    }
    Serial2.write(num);
    //////////////////////////////////////////
    if (Serial1.available() > 0)
    {
      conditionRec = Serial1.read();
    }

    if (condition != conditionRec) {
      delay(100);
      Serial1.write(condition);         //отправляем состояние "приветствия" контроллеру управления светом
      //Serial.println(condition);
      conditionOld = condition;
    }
    if (condition == 9 || condition == 10)
    {
      eyeLeft(60);
      eyeRight(60);
    }
    if (condition == 11 || condition == 12)
    {
      eyeLeft(20);
      eyeRight(20);
    }
    if (condition == 19 || condition == 20)
    {
      eyeLeft(40);
      eyeRight(10);
    }
    if (Serial1.available() > 0)
    {
      condition = Serial1.read();
      Serial1.write(condition);
    }
    ///////////////////////////////////////

    switch (condition)
    {
      case 1:
        eyeLeft(50);
        eyeRight(50);
        myDFPlayer.play(1);
        myTimerCond = millis();//привествие
        condition++;
        break;
      case 2:
        if (millis() - myTimerCond > 10000)
          condition++;
        break;
      case 3:
        myDFPlayer.play(2);             //я умею показывать различные эмоции
        myTimerCond = millis();
        condition++;
        break;
      case 4:
        if (millis() - myTimerCond > 4000) {
          condition++;
        }
        break;
      case 5:
        myDFPlayer.play(3);           //радость
        myTimerCond = millis();
        condition++;
        break;
      case 6:
        if (millis() - myTimerCond > 2000) {
          condition++;
        }
        break;
      case 7:
        myDFPlayer.play(4);          //грусть/
        myTimerCond = millis();
        condition++;
        break;
      case 8:
        if (millis() - myTimerCond > 2000) {
          condition++;
        }
        break;
      case 9:
        myDFPlayer.play(5);         //удивление
        myTimerCond = millis();
        condition++;
        break;
      case 10:
        if (millis() - myTimerCond > 2000) {
          condition++;
        }
        break;
      case 11:
        eyeLeft(20);
        eyeRight(20);
        myDFPlayer.play(6);       //злость
        myTimerCond = millis();
        condition++;
        break;
      case 12:
        if (millis() - myTimerCond > 2000) {
          condition++;
        }
        break;
      case 13:
        eyeLeft(50);
        eyeRight(50);
        myDFPlayer.play(7);     //смущение
        myTimerCond = millis();
        condition++;
        break;
      case 14:
        if (millis() - myTimerCond > 3000) {
          condition++;
        }
        break;
      case 15:
        myDFPlayer.play(8);    //нейтральное
        myTimerCond = millis();
        condition++;
        break;
      case 16:
        if (millis() - myTimerCond > 3000) {
          condition++;
        }
        break;
      case 17:
        myDFPlayer.play(9);    //А еще я умею
        myTimerCond = millis();
        condition++;
        break;
      case 18:
        if (millis() - myTimerCond > 3000) {
          condition++;
        }
        break;
      case 19:
        eyeRight(10);
        myDFPlayer.play(11);    //подмигивать
        myTimerCond = millis();
        condition++;
        break;
      case 20:
        if (millis() - myTimerCond > 3000) {
          condition++;
        }
        break;
        /*case 21:
          delay(1000);
          break;*/
        /* case 23:
           myDFPlayer.play(12);    //имитировать ходьбу
           condition++;
           break;
          case 24:
           if (millis() - myTimerCondw > 40000) {
             condition++;
           }
           break;*/
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
