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

#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(9600);        //инициализируем UART с плеером
  delay(1000);
  myDFPlayer.begin(Serial3);  //инициализируем плеер

  myDFPlayer.volume(20);  //Установка громкости от 0 до 30

  myDFPlayer.play(1);     //Играть первый трек
  delay(3000);
  myDFPlayer.pause();//*/     
  Serial.print(0);
}

void loop()
{
  
/*  if(Serial1.available() > 0)
    {
      int a = Serial1.read();
      switch(a)
      {
        case 1: myDFPlayer.play(1); break;
        case 2: myDFPlayer.play(2); break;
        case 3: myDFPlayer.play(3); break;
        case 4: myDFPlayer.play(4); break;
        case 5: myDFPlayer.play(5); break;
        default: myDFPlayer.pause(); break; 
      }
      Serial.print(a); 
    }*/
}
