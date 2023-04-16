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

int condition = 0, conditionRec = 0, conditionFuture = 0, conditionOld = -1, caseOld = -1;
bool exercise = 0;
bool greetings = 0;
int tagShowed = -1;
int End = 0;
int tagReal = 0;
int tagShowedBefore = -1;
int8_t arrayExercise[6] = {7, 5, 15, 11, 13, 9};
int8_t arrayExerciseOld[6] = { -1, -1, -1, -1, -1, -1};

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
  (millis() % 200 > 100) ? digitalWrite(13, 1) : digitalWrite(13, 0); //пример короткой записи if/else

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

  if (Serial2.available() > 0)        //связь с нижней платформой
  {
    tagShowed = Serial2.read();
    Serial.println(tagShowed);
    Serial2.write(tagShowed);
    if (tagShowed == 7)
    {
      condition = 25;
      exercise = 1;
      greetings = 0;
    }
    else if (tagShowed == 6)
    {
      condition = 1;
      greetings = 1;
      exercise = 0;
    }
    else if (exercise && tagShowed != tagReal)  //Неверный ответ
      condition = 29;
    else if (exercise && tagShowed == tagReal)  //Верный ответ
    {
      End++;
      caseOld = conditionFuture;
      if (End >= 6)
      {
        condition = 32;
        End = 0;
        for (int i = 0; i < 6; i++)
          arrayExerciseOld[i] = -1;
      }
      else
      {
        condition = 27;
        conditionFuture = arrayExercise[(analogRead(0) % 6)];
        for (int i = 0; i < 6; i++)                           //защита повтора
          if (arrayExerciseOld[i] == conditionFuture)
          {
            conditionFuture = arrayExercise[(analogRead(0) % 6)];
            i = 0;
          }
        arrayExerciseOld[End] = conditionFuture;
      }
    }
  }
  //////////////////////////////////////////

  if (Serial1.available() > 0)
  {
    conditionRec = Serial1.read();
  }

  if (condition != conditionRec)
  {
    //delay(100);
    Serial.print(condition);
    Serial.print("\tТэг:  ");
    Serial.println(tagShowed);
    Serial1.write(condition);         //отправляем состояние контроллеру управления светом
  }

  /*if (Serial1.available() > 0)
    {
    condition = Serial1.read();
    Serial1.write(condition);
    }*/
  ///////////////////////////////////////

  switch (condition)
  {
    case 1:                           //привествие
      myDFPlayer.play(1);
      timerCond = millis();
      condition++;
      break;
    case 2:
     // eyepupilLeft.write(90);
   //   eyepupilRight.write(90);
      if (millis() - timerCond > 5000)
        condition++;
      break;
    case 3:
      myDFPlayer.play(2);             //я умею показывать различные эмоции
      timerCond = millis();
      condition++;
      break;
    case 4:
      if (millis() - timerCond > 4000) {
        condition++;
      }
      break;
    case 5:                           //звук: радость///////////////////////////////
      if (greetings)
        myDFPlayer.play(3);
      timerCond = millis();
      tagReal = 1;
      condition++;
      break;
    case 6:                           //радость
      if (exercise)
        conditionOld = condition - 1;
      if (greetings)
        if (millis() - timerCond > 2000)
          condition++;
      break;
    case 7:
      if (greetings)
        myDFPlayer.play(4);           //звук: грусть////////////////////////////////
      timerCond = millis();
      tagReal = 0;
      condition++;
      break;
    case 8:
      if (exercise)
        conditionOld = condition - 1;
      if (greetings)
        if (millis() - timerCond > 2000)
          condition++;
      break;
    case 9:
      if (greetings)
        myDFPlayer.play(5);         //удивление
      timerCond = millis();
      tagReal = 5;
      condition++;
      break;
    case 10:
      eyeLeft(60);
      eyeRight(60);
      if (exercise)
        conditionOld = condition - 1;
      if (greetings)
        if (millis() - timerCond > 2000)
          condition++;
      break;
    case 11:
      if (greetings)
        myDFPlayer.play(6);       //злость
      timerCond = millis();
      tagReal = 3;
      condition++;
      break;
    case 12:
      eyeLeft(20);
      eyeRight(20);
      if (exercise)
        conditionOld = condition - 1;
      if (greetings)
        if (millis() - timerCond > 2000)
          condition++;
      break;
    case 13:                     //смущение////////////////////
      eyeLeft(50);
      eyeRight(50);
      if (greetings)
        myDFPlayer.play(7);     //смущение
      timerCond = millis();
      tagReal = 4;
      condition++;
      break;
    case 14:
      if (exercise)
      {
        conditionOld = condition - 1;
        condition == 31;
      }

      if (greetings)
        if (millis() - timerCond > 2000)
          condition++;
      break;
    case 15:
      if (greetings)
        myDFPlayer.play(8);         //нейтральное
      timerCond = millis();
      tagReal = 2;
      condition++;
      break;
    case 16:
      if (exercise)
        conditionOld = condition - 1;
      if (greetings)
        if (millis() - timerCond > 2000)
          condition++;
      break;
    case 17:
      myDFPlayer.play(9);    //А еще я умею
      timerCond = millis();
      condition++;
      break;
    case 18:
      if (millis() - timerCond > 3000) {
        condition++;
      }
      break;
    case 19:
      eyeRight(10);
      myDFPlayer.play(10);    //подмигивать
      timerCond = millis();
      condition++;
      break;
    case 20:
      eyeLeft(40);
      eyeRight(10);
      if (millis() - timerCond > 3000)
        condition++;
      break;
    case 21:                      //имитировать ходьбу
      myDFPlayer.play(11);
      Serial2.write(char(100));
      condition++;
      timerCond = millis();
      break;
    case 22:
      if (millis() - timerCond > 8000) {
        condition++;
        Serial2.write(char(101));
      }
      break;
    case 23:
      myDFPlayer.play(15);
      timerCond = millis();
      condition++;
      break;
    case 24:
      if (millis() - timerCond > 5000)
        condition = 0;
      break;
    case 25:
      exercise = 1;
      greetings = 0;
      myDFPlayer.play(16);    //давай поиграем
      condition++;
      break;
    case 26:
      if (millis() - timerCond > 9000)
      {
        arrayExerciseOld[0] = arrayExercise[(analogRead(0) % 6)];
        condition = arrayExerciseOld[0];
      }
      break;
    case 27:
      myDFPlayer.play(14);    //молодец, верно
      timerCond = millis();
      condition++;
      break;
    case 28:
      if (millis() - timerCond > 3000) {
        condition = conditionFuture;
      }
      break;
    case 29:
      myDFPlayer.play(13);    //неверно, подумай еще
      timerCond = millis();
      condition++;
      break;
    case 30:
      if (millis() - timerCond > 3000)
      {
        condition = conditionOld;
      }
      break;
    case 31:
      condition = 27;
      break;
    case 32:
      myDFPlayer.play(18);    //Молодец, ты прошел игру
      timerCond = millis();
      condition++;
      break;
    case 33:
      if (millis() - timerCond > 5000)
        condition = 0;
      break;
    default: break;

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
