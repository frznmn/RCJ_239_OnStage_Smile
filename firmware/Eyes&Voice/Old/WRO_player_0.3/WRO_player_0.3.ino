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

int currentPosition = 0;
int desiredPosition = 0;

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
  
  myTimer1 = millis();
  desiredPosition = 40;       //желаемая позиция век
  while (millis() - myTimer1 < 2000)    //плавное движение серв
    if (millis() - myTimer2 > 20)
    {
      myTimer2 = millis();
      eye();
    }
  
  myDFPlayer.volume(20);      //Установка громкости от 0 до 30

  Serial1.write(1);           //отправляем состояние "приветствия" контроллеру управления светом
  myDFPlayer.play(6);         //Аудизапись приветствие
  delay(10000);
  Serial1.write(2);
  myDFPlayer.play(2);        //Аудизапись злость
  delay(3000);
  myDFPlayer.pause();         //пауза
}

void loop()
{

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
