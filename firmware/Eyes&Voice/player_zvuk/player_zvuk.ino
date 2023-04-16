#include <SD.h>
#include <SPI.h>
#include <MusicPlayer.h>

void setup()
{
  player.begin();
}

void loop()
{
  player.playOne("snake.mp3");//proigryvanie opredelyonogo faila
  player.play(); //komanda proigryvaniya audiofaila
  delay(5000); 
  player.opStop(); //ostanovka proigryvania
  delay(5000);
}
