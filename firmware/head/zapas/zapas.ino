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
#define HEART_PIN 32

#define APDS9960_INT 19    // Указываем вывод прерывания
#define NUMPIXELS_EYES 12  // указываем количество светодиодов в ленте
#define NUMPIXELS_MOUTH 15
#define NUMPIXELS_HEART 64

// создаем объект strip с нужными характеристиками
Adafruit_NeoPixel eyeL(NUMPIXELS_EYES, EYE_L_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel eyeR(NUMPIXELS_EYES, EYE_R_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mouth(NUMPIXELS_MOUTH, MOUTH_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel heart(NUMPIXELS_HEART, HEART_PIN, NEO_GRB + NEO_KHZ800);

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
  heart.begin();                // инициализируем ленту
  heart.setBrightness(BRIGHT);  // указываем яркость светодиодов (максимум 255)
  heart.clear();
  mouth.clear();
  eyeL.clear();
  eyeR.clear();
  eyeR.show();
  eyeL.show();
  mouth.show();
  heart.show();
  earL.attach(EAR_L);  // attaches the servo on pin 9 to the servo object
  earR.attach(EAR_R);
  earL.write(90);  // tell servo to go to position in variable 'pos'
  earR.write(90);
  pinMode(pinD0, INPUT);
}

void motor(int m) {
  digitalWrite(4, LOW);
  m = abs(m);
  if (m > 255) m = 255;
  analogWrite(5, m);
}

void calm() {
  for (int i = 3; i <= 9; i++) {
    eyeL.setPixelColor(i, eyeL.Color(255, 255, 255));  // включаем белый цвет на 3 светодиоде
    eyeR.setPixelColor(i, eyeR.Color(255, 255, 255));
  }
  for (int i = 5; i <= 9; i++) {
    mouth.setPixelColor(i, mouth.Color(120, 0, 120));
  }
  earL.write(90);
  earR.write(90);
  eyeL.show();  // отправляем сигнал на ленту
  eyeR.show();
  mouth.show();
}

void REDheart_on() {
  heart.setPixelColor(59, heart.Color(255, 0, 0));
  heart.setPixelColor(60, heart.Color(255, 0, 0));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(53, heart.Color(255, 0, 0));
  heart.setPixelColor(52, heart.Color(255, 0, 0));
  heart.setPixelColor(51, heart.Color(255, 0, 0));
  heart.setPixelColor(50, heart.Color(255, 0, 0));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(46, heart.Color(255, 0, 0));
  heart.setPixelColor(45, heart.Color(255, 0, 0));
  heart.setPixelColor(44, heart.Color(255, 0, 0));
  heart.setPixelColor(43, heart.Color(255, 0, 0));
  heart.setPixelColor(42, heart.Color(255, 0, 0));
  heart.setPixelColor(41, heart.Color(255, 0, 0));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(39, heart.Color(255, 0, 0));
  heart.setPixelColor(38, heart.Color(255, 0, 0));
  heart.setPixelColor(37, heart.Color(255, 0, 0));
  heart.setPixelColor(36, heart.Color(255, 0, 0));
  heart.setPixelColor(35, heart.Color(255, 0, 0));
  heart.setPixelColor(34, heart.Color(255, 0, 0));
  heart.setPixelColor(33, heart.Color(255, 0, 0));
  heart.setPixelColor(32, heart.Color(255, 0, 0));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(31, heart.Color(255, 0, 0));
  heart.setPixelColor(30, heart.Color(255, 0, 0));
  heart.setPixelColor(29, heart.Color(255, 0, 0));
  heart.setPixelColor(28, heart.Color(255, 0, 0));
  heart.setPixelColor(27, heart.Color(255, 0, 0));
  heart.setPixelColor(26, heart.Color(255, 0, 0));
  heart.setPixelColor(25, heart.Color(255, 0, 0));
  heart.setPixelColor(24, heart.Color(255, 0, 0));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(23, heart.Color(255, 0, 0));
  heart.setPixelColor(22, heart.Color(255, 0, 0));
  heart.setPixelColor(21, heart.Color(255, 0, 0));
  heart.setPixelColor(20, heart.Color(255, 0, 0));
  heart.setPixelColor(19, heart.Color(255, 0, 0));
  heart.setPixelColor(18, heart.Color(255, 0, 0));
  heart.setPixelColor(17, heart.Color(255, 0, 0));
  heart.setPixelColor(16, heart.Color(255, 0, 0));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(15, heart.Color(255, 0, 0));
  heart.setPixelColor(14, heart.Color(255, 0, 0));
  heart.setPixelColor(13, heart.Color(255, 0, 0));
  heart.setPixelColor(10, heart.Color(255, 0, 0));
  heart.setPixelColor(9, heart.Color(255, 0, 0));
  heart.setPixelColor(8, heart.Color(255, 0, 0));
  heart.show();  // отправляем сигнал на ленту

  heart.setPixelColor(6, heart.Color(255, 0, 0));
  heart.setPixelColor(1, heart.Color(255, 0, 0));
  heart.show();  // отправляем сигнал на ленту
}

void heart_on() {
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

void trash(int x) {
  // motor(100);
  for (int j = 1; j <= 3; j++) {
    switch (x) {
      case 1:
        for (int i = 0; i <= 15; i++) {
          eyeL.setPixelColor(i, eyeL.Color(0, 255, 0));  // включаем белый цвет на 3 светодиоде
          eyeR.setPixelColor(i, eyeR.Color(0, 255, 0));
          mouth.setPixelColor(i, mouth.Color(0, 255, 0));
        }
        for (int i = 70; i <= 110; i++) {
          earL.write(i);  // tell servo to go to position in variable 'pos'
          earR.write(i);
          delay(2);
        }
        eyeL.show();  // отправляем сигнал на ленту
        eyeR.show();
        mouth.show();
        delay(500);
        for (int i = 0; i <= 15; i++) {
          eyeL.setPixelColor(i, eyeL.Color(0, 0, 0));  // включаем белый цвет на 3 светодиоде
          eyeR.setPixelColor(i, eyeR.Color(0, 0, 0));
          mouth.setPixelColor(i, mouth.Color(0, 0, 0));
        }
        for (int i = 110; i >= 70; i--) {
          earL.write(i);  // tell servo to go to position in variable 'pos'
          earR.write(i);
          delay(5);
        }
        eyeL.show();  // отправляем сигнал на ленту
        eyeR.show();
        mouth.show();

        for (int i = 0; i <= 7; i++) {
          heart.setPixelColor(i, heart.Color(255, 0, 0));
          heart.setPixelColor(8 + i, heart.Color(255, 0, 0));
          heart.setPixelColor(16 + i, heart.Color(255, 0, 0));
        }

        delay(500);
        break;
      case 2:
        for (int i = 0; i <= 15; i++) {
          eyeL.setPixelColor(i, eyeL.Color(0, 0, 255));  // включаем белый цвет на 3 светодиоде
          eyeR.setPixelColor(i, eyeR.Color(0, 0, 255));
          mouth.setPixelColor(i, mouth.Color(0, 0, 255));
        }
        for (int i = 70; i <= 110; i++) {
          earL.write(i);  // tell servo to go to position in variable 'pos'
          earR.write(i);
          delay(2);
        }
        eyeL.show();  // отправляем сигнал на ленту
        eyeR.show();
        mouth.show();
        delay(500);
        for (int i = 0; i <= 15; i++) {
          eyeL.setPixelColor(i, eyeL.Color(0, 0, 0));  // включаем белый цвет на 3 светодиоде
          eyeR.setPixelColor(i, eyeR.Color(0, 0, 0));
          mouth.setPixelColor(i, mouth.Color(0, 0, 0));
        }
        for (int i = 110; i >= 70; i--) {
          earL.write(i);  // tell servo to go to position in variable 'pos'
          earR.write(i);
          delay(2);
        }

        for (int i = 0; i <= 7; i++) {
          heart.setPixelColor(24 + i, heart.Color(255, 0, 0));
          heart.setPixelColor(32 + i, heart.Color(255, 0, 0));
          heart.setPixelColor(40 + i, heart.Color(255, 0, 0));
        }

        eyeL.show();  // отправляем сигнал на ленту
        eyeR.show();
        mouth.show();
        delay(500);
        break;
      case 3:
        for (int i = 0; i <= 15; i++) {
          eyeL.setPixelColor(i, eyeL.Color(0, 255, 255));  // включаем белый цвет на 3 светодиоде
          eyeR.setPixelColor(i, eyeR.Color(0, 255, 255));
          mouth.setPixelColor(i, mouth.Color(0, 255, 255));
        }
        for (int i = 70; i <= 110; i++) {
          earL.write(i);  // tell servo to go to position in variable 'pos'
          earR.write(i);
          delay(5);
        }
        eyeL.show();  // отправляем сигнал на ленту
        eyeR.show();
        mouth.show();
        delay(500);
        for (int i = 0; i <= 15; i++) {
          eyeL.setPixelColor(i, eyeL.Color(0, 0, 0));  // включаем белый цвет на 3 светодиоде
          eyeR.setPixelColor(i, eyeR.Color(0, 0, 0));
          mouth.setPixelColor(i, mouth.Color(0, 0, 0));
        }
        for (int i = 110; i >= 70; i--) {
          earL.write(i);  // tell servo to go to position in variable 'pos'
          earR.write(i);
          delay(5);
        }
        eyeL.show();  // отправляем сигнал на ленту
        eyeR.show();
        mouth.show();

        for (int i = 0; i <= 7; i++) {
          heart.setPixelColor(48 + i, heart.Color(255, 0, 0));
          heart.setPixelColor(56 + i, heart.Color(255, 0, 0));
        }

        delay(500);
        break;
    }
  }

  heart.show();
  c = 0;
  eyeL.clear();
  eyeR.clear();
  mouth.clear();

  // motor(0);
}

void kind() {
  heart.clear();
  heart.show();
  heart_on();
  for (int i = 0; i <= 15; i++) {
    eyeL.setPixelColor(i, eyeL.Color(0, 255, 255));  // включаем белый цвет на 3 светодиоде
    eyeR.setPixelColor(i, eyeR.Color(0, 255, 255));
    eyeL.show();
    eyeR.show();
    delay(200);
  }
  for (int i = 3; i <= 11; i++) {
    mouth.setPixelColor(i, mouth.Color(0, 255, 255));
  }
  mouth.show();
  for (int i = 70; i <= 110; i++) {
    earL.write(i);  // tell servo to go to position in variable 'pos'
    earR.write(i);
    delay(5);
  }
  delay(100);
  for (int i = 110; i >= 70; i--) {
    earL.write(i);  // tell servo to go to position in variable 'pos'
    earR.write(i);
    delay(5);
  }
}

void angry() {
  for (int i = 0; i <= 15; i++) {
    eyeL.setPixelColor(i, eyeL.Color(255, 0, 0));  // включаем белый цвет на 3 светодиоде
    eyeR.setPixelColor(i, eyeR.Color(255, 0, 0));
  }
  mouth.setPixelColor(6, mouth.Color(255, 0, 0)); 
    mouth.setPixelColor(7, mouth.Color(255, 0, 0)); 
    mouth.setPixelColor(8, mouth.Color(255, 0, 0));
mouth.show();
  eyeL.show();
  eyeR.show();
  REDheart_on();
  while (true) {
     for (int i = 6; i >= 0; i--)
    {
      earL.write(-i * 80 / 6 + 130);
      earR.write(-i * 80 / 6 + 130);
        mouth.setPixelColor(i, mouth.Color(255, 0, 0));
        mouth.setPixelColor(14-i, mouth.Color(255, 0, 0));
       mouth.show();
       delay(50);
    }
     delay(100);
    for (int i = 0; i <= 6; i++)
    {
      earL.write(i * 80 / 6 + 50);
      earR.write(i * 80 / 6 + 50);
       mouth.setPixelColor(i, mouth.Color(0, 0, 0));
        mouth.setPixelColor(14-i, mouth.Color(0, 0, 0));
       mouth.show();
       delay(5);
    }
  }
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
        trash(1);
        break;
      case 2:
        trash(2);
        break;
      case 3:
        trash(3);
        break;
      case 4:
        kind();
        break;
      case 5:
        angry();
        break;
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
      case DIR_DOWN:
        Serial.println("DOWN");
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