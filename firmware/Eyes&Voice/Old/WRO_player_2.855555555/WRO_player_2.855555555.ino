#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini myDFPlayer;

#include <Servo.h>

#define CLOSE_LEFT_EYE 60
#define CLOSE_RIGHT_EYE 0
#define CLOSE_LEFT_PUPIL 30
#define CLOSE_RIGHT_PUPIL 40
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
bool flag = true;
bool last_words = false;
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

  eyepupilLeft.attach(9);      //инициализируем сервопривод левой брови 8
  eyepupilRight.attach(8);     //инициализируем сервопривод правой брови 9

  myTimerEyeLeft = millis();  //Обнуляем таймер
  myTimerEyeRight = millis();
  myTimerPupilLeft = millis();
  myTimerPupilRight = millis();
  timerCond = millis();     //Обнуляем таймер

  pinMode(13, 1);
  //  pupilLeft(0);
  //pupilRight(0);
  Serial.begin(9600);
}

void eyeLeft(int desiredPosition) // Функция управления левым глазом
{
  static int currentPosition = 0;

  if (currentPosition > desiredPosition)
    currentPosition -= 1;
  else if (currentPosition < desiredPosition)
    currentPosition += 1;

  eyelidLeft.write(CLOSE_LEFT_EYE - currentPosition);
}

void eyeRight(int desiredPosition)  // Функция управления левым глазом
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
  /* if (flag) {
     pupilLeft(0);
     pupilRight(0);
    }*/
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
    case 1:                           //смех
      myDFPlayer.play(24);
      timerCond = millis();
      condition++;
      break;
    case 2:
      // eyepupilLeft.write(90);
      //   eyepupilRight.write(90);
      if (millis() - timerCond > 3000)
        condition++;
      break;
    case 3:                           //как
      myDFPlayer.play(23);
      timerCond = millis();
      condition++;
      break;
    case 4:
      // eyepupilLeft.write(90);
      //   eyepupilRight.write(90);
      if (millis() - timerCond > 120000)
        condition++;
      break;





    case 5:
      tagShowed = Serial2.read();
      if (tagShowed == 2)
      {
        last_words = true;
        Serial.println("222");
        myDFPlayer.play(25);
        if (last_words == true)
        { //голова

          timerCond = millis();
          condition++;
          break;
        }
      }
    case 6:
      // eyepupilLeft.write(90);
      //   eyepupilRight.write(90);
      if (millis() - timerCond > 3000)
        condition++;
      break;
    case 7:                           //семья
      myDFPlayer.play(26);
      timerCond = millis();
      condition++;
      break;
    case 8:
      // eyepupilLeft.write(90);
      //   eyepupilRight.write(90);
      if (millis() - timerCond > 3000)
        condition++;
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
