#include "Adafruit_NeoPixel.h"  // подключаем библиотеку

#define BRIGHT 20

#define EYE_L_PIN 33  // указываем пин для подключения ленты
#define EYE_R_PIN 35
#define MOUTH_PIN 34

#define NUMPIXELS_EYES 12  // указываем количество светодиодов в ленте
#define NUMPIXELS_MOUTH 15

// создаем объект strip с нужными характеристиками
Adafruit_NeoPixel eyeL(NUMPIXELS_EYES, EYE_L_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel eyeR(NUMPIXELS_EYES, EYE_R_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mouth(NUMPIXELS_MOUTH, MOUTH_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  eyeL.begin();             // инициализируем ленту
  eyeL.setBrightness(BRIGHT);   // указываем яркость светодиодов (максимум 255)
  eyeR.begin();             // инициализируем ленту
  eyeR.setBrightness(BRIGHT);   // указываем яркость светодиодов (максимум 255)
  mouth.begin();            // инициализируем ленту
  mouth.setBrightness(BRIGHT);  // указываем яркость светодиодов (максимум 255)
}

void loop() {

  for (int i = 0; i <= NUMPIXELS_MOUTH; i++) {
    eyeL.setPixelColor(i, eyeL.Color(102, 200, 255));  // включаем белый цвет на 3 светодиоде
    eyeR.setPixelColor(i, eyeR.Color(102, 0, 255));
    mouth.setPixelColor(i, mouth.Color(255, 0, 0));
    eyeL.show();  // отправляем сигнал на ленту
    eyeR.show();
    mouth.show();
    delay(200);
  }
  eyeL.clear();  // выключаем все светодиоды
  eyeR.clear();
  mouth.clear();
}