#include <SD.h>
#include <SPI.h>
char recivSerial = " ";
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Andronov privetstvuet Vas!\n\n");
  player.begin();
}

void loop(void)
{ 
  if (Serial.available() > 0)
  { 
    recivSerial = Serial.read();
    
    if (recivSerial == '1')
    { 
      player.playOne("snake.mp3");
      player.play();
    }

    else if (recivSerial == '2')
    { 
      player.playOne("snake2.mp3");
      player.play();
    }

    else if (recivSerial == '3')
    { 
      player.playOne("snake3.MP3");
      player.play();
    }
    else if (recivSerial == '4')
    { 
      player.opStop();
      
    }


  }
}
