#include <Adafruit_NeoPixel.h>
//KY-031 датчик удара
int led = 13 ;        // встроенный в адуино светодиод
int shockSensor = 36; // пин для подключения датчика
int value;            // переменная для хранения состояния датчика

Adafruit_NeoPixel strip(15, 32, NEO_GRB + NEO_KHZ800);

void setup ()
{
strip.begin();
strip.setBrightness(100);
  pinMode (led, OUTPUT) ;        // назначение выхода для светодиода
  pinMode (shockSensor, INPUT) ; // назначение входа для датчика
}
void loop ()
{
  value = digitalRead (shockSensor) ; // чтение состояния датчика
  if (value == HIGH) // когда датчик детектирует удар, светодиод загорается 
  {
    digitalWrite (led, HIGH);
    for (int i = 0; i <= 15; i++) {
    strip.setPixelColor(i, strip.Color(102, 200, 255));  // включаем белый цвет на 3 светодиоде
    }
    strip.show();
  }
  else              // иначе светодиод тухнет
  {
    digitalWrite (led, LOW);
    strip.clear();
    strip.show();
  }
}