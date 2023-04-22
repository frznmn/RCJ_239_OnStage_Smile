#include <Wire.h>               // Подключаем библиотеку Wire
#include <SparkFun_APDS9960.h>  // Подключаем библиотеку SparkFun_APDS9960
#include "Adafruit_NeoPixel.h"  // подключаем библиотеку
#include <Servo.h>

#define EAR_L 3
#define EAR_R 5

Servo earL;  // create servo object to control a servo
Servo earR;

int pinD0 = 36;  // Пин к которому подключен D0
int motionDetected = 0;
int sensorVal = 0;
int naprav = 1;

#define BRIGHT 20

#define EYE_L_PIN 33  // указываем пин для подключения ленты
#define EYE_R_PIN 35
#define MOUTH_PIN 34
#define APDS9960_INT 19    // Указываем вывод прерывания
#define NUMPIXELS_EYES 12  // указываем количество светодиодов в ленте
#define NUMPIXELS_MOUTH 15

// создаем объект strip с нужными характеристиками
Adafruit_NeoPixel eyeL(NUMPIXELS_EYES, EYE_L_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel eyeR(NUMPIXELS_EYES, EYE_R_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mouth(NUMPIXELS_MOUTH, MOUTH_PIN, NEO_GRB + NEO_KHZ800);

SparkFun_APDS9960 apds = SparkFun_APDS9960();  // Создаем объект
int isr_flag = 0;                              // Создаем переменную isr_flag
int count = 0, c = 0;

void setup() {

  // Инициализируем последовательную связь и отправляем сообщения
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  // Инициализируем прерывание на спад
  attachInterrupt(4, interruptRoutine, FALLING);

  // Инициализируем APDS-9960
  if (apds.init()) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  if (apds.enableGestureSensor(true)) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
  eyeL.begin();                 // инициализируем ленту
  eyeL.setBrightness(BRIGHT);   // указываем яркость светодиодов (максимум 255)
  eyeR.begin();                 // инициализируем ленту
  eyeR.setBrightness(BRIGHT);   // указываем яркость светодиодов (максимум 255)
  mouth.begin();                // инициализируем ленту
  mouth.setBrightness(BRIGHT);  // указываем яркость светодиодов (максимум 255)

  earL.attach(EAR_L);  // attaches the servo on pin 9 to the servo object
  earR.attach(EAR_R);
  earL.write(90);  // tell servo to go to position in variable 'pos'
  earR.write(90);
  pinMode(pinD0, INPUT);
}

void calm() {
  for (int i = 3; i <= 9; i++) {
    eyeL.setPixelColor(i, eyeL.Color(255, 255, 255));  // включаем белый цвет на 3 светодиоде
    eyeR.setPixelColor(i, eyeR.Color(255, 255, 255));
  }
  for (int i = 5; i <= 9; i++) {
    mouth.setPixelColor(i, mouth.Color(120, 0, 120));
  }
  eyeL.show();  // отправляем сигнал на ленту
  eyeR.show();
  mouth.show();
}

void trash(int x) {
  switch (x) {
    case 1:
      for (int i = 3; i <= 9; i++) {
        eyeL.setPixelColor(i, eyeL.Color(0, 255, 0));  // включаем белый цвет на 3 светодиоде
        eyeR.setPixelColor(i, eyeR.Color(0, 255, 0));
        mouth.setPixelColor(i, mouth.Color(0, 255, 0));
      }
      eyeL.show();  // отправляем сигнал на ленту
      eyeR.show();
      mouth.show();
    case 2:
      for (int i = 3; i <= 9; i++) {
        eyeL.setPixelColor(i, eyeL.Color(0, 0, 255));  // включаем белый цвет на 3 светодиоде
        eyeR.setPixelColor(i, eyeR.Color(0, 0, 255));
        mouth.setPixelColor(i, mouth.Color(0, 0, 255));
      }
      eyeL.show();  // отправляем сигнал на ленту
      eyeR.show();
      mouth.show();
    case 3:
      for (int i = 3; i <= 9; i++) {
        eyeL.setPixelColor(i, eyeL.Color(0, 255, 255));  // включаем белый цвет на 3 светодиоде
        eyeR.setPixelColor(i, eyeR.Color(0, 255, 255));
        mouth.setPixelColor(i, mouth.Color(0, 255, 255));
      }
      mouth.setPixelColor(10, mouth.Color(0, 255, 255));
      mouth.setPixelColor(11, mouth.Color(0, 255, 255));

      eyeL.show();  // отправляем сигнал на ленту
      eyeR.show();
      mouth.show();
  }
   motionDetected = digitalRead(pinD0);  // Считываем показания
  if (motionDetected) {
    naprav *= -1;
    if (naprav > 0) {
      for (int i = 70; i < 110; i++) {
        earL.write(i);  // tell servo to go to position in variable 'pos'
        earR.write(i);
        delay(5);
      }
    } else {
      for (int i = 110; i > 70; i--) {
        earL.write(i);  // tell servo to go to position in variable 'pos'
        earR.write(i);
        delay(5);
      }
    }
  }
  delay(2000);
  c = 0;
  eyeL.clear();
  eyeR.clear();
  mouth.clear();
}

void loop() {
  if (isr_flag == 1) {
    detachInterrupt(4);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(4, interruptRoutine, FALLING);
  }
  if (c) {
    switch (count) {
      case 1:
        trash(count);
      case 2:
        trash(count);
      case 3:
        trash(count);
        // case 4:
        //   kind();
        // case 5:
        //   angry();
    }
  } else {
    calm();
  }
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
  if (apds.isGestureAvailable()) {
    // Serial.println("uuuu");
    switch (apds.readGesture()) {
      case DIR_UP:
        Serial.println("UP");
        count += 1;
        c = 1;
        break;
      // case DIR_LEFT:
      //   Serial.println("LEFT");
      //   break;
      // case DIR_RIGHT:
      //   Serial.println("RIGHT");
      //   break;
      // case DIR_NEAR:
      //   Serial.println("NEAR");
      //   break;
      // case DIR_FAR:
      //   Serial.println("FAR");
      //   break;
      default:
        Serial.println("NONE");
    }
  }
}