#include "Adafruit_NeoPixel.h"  // подключаем библиотеку

#define BRIGHT 20

#define HEART_PIN 32  // указываем пин для подключения ленты

#define NUMPIXELS_HEART 64  // указываем количество светодиодов в ленте

// создаем объект strip с нужными характеристиками
Adafruit_NeoPixel heart(NUMPIXELS_HEART, HEART_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  heart.begin();                // инициализируем ленту
  heart.setBrightness(BRIGHT);  // указываем яркость светодиодов (максимум 255)
  heart.clear();
  delay(500);
}

void loop() {
  heart.setPixelColor(59, heart.Color(255, 0, 255));
  heart.setPixelColor(60, heart.Color(255, 0, 255));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(53, heart.Color(255, 0, 255));
  heart.setPixelColor(52, heart.Color(255, 0, 255));
  heart.setPixelColor(51, heart.Color(255, 0, 255));
  heart.setPixelColor(50, heart.Color(255, 0, 255));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(46, heart.Color(255, 0, 255));
  heart.setPixelColor(45, heart.Color(255, 0, 255));
  heart.setPixelColor(44, heart.Color(255, 0, 255));
  heart.setPixelColor(43, heart.Color(255, 0, 255));
  heart.setPixelColor(42, heart.Color(255, 0, 255));
  heart.setPixelColor(41, heart.Color(255, 0, 255));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(39, heart.Color(255, 0, 255));
  heart.setPixelColor(38, heart.Color(255, 0, 255));
  heart.setPixelColor(37, heart.Color(255, 0, 255));
  heart.setPixelColor(36, heart.Color(255, 0, 255));
  heart.setPixelColor(35, heart.Color(255, 0, 255));
  heart.setPixelColor(34, heart.Color(255, 0, 255));
  heart.setPixelColor(33, heart.Color(255, 0, 255));
  heart.setPixelColor(32, heart.Color(255, 0, 255));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(31, heart.Color(255, 0, 255));
  heart.setPixelColor(30, heart.Color(255, 0, 255));
  heart.setPixelColor(29, heart.Color(255, 0, 255));
  heart.setPixelColor(28, heart.Color(255, 0, 255));
  heart.setPixelColor(27, heart.Color(255, 0, 255));
  heart.setPixelColor(26, heart.Color(255, 0, 255));
  heart.setPixelColor(25, heart.Color(255, 0, 255));
  heart.setPixelColor(24, heart.Color(255, 0, 255));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(23, heart.Color(255, 0, 255));
  heart.setPixelColor(22, heart.Color(255, 0, 255));
  heart.setPixelColor(21, heart.Color(255, 0, 255));
  heart.setPixelColor(20, heart.Color(255, 0, 255));
  heart.setPixelColor(19, heart.Color(255, 0, 255));
  heart.setPixelColor(18, heart.Color(255, 0, 255));
  heart.setPixelColor(17, heart.Color(255, 0, 255));
  heart.setPixelColor(16, heart.Color(255, 0, 255));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(15, heart.Color(255, 0, 255));
  heart.setPixelColor(14, heart.Color(255, 0, 255));
  heart.setPixelColor(13, heart.Color(255, 0, 255));
  heart.setPixelColor(10, heart.Color(255, 0, 255));
  heart.setPixelColor(9, heart.Color(255, 0, 255));
  heart.setPixelColor(8, heart.Color(255, 0, 255));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(6, heart.Color(255, 0, 255));
  heart.setPixelColor(1, heart.Color(255, 0, 255));
  heart.show();  // отправляем сигнал на ленту


}