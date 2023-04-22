#include <Servo.h>

#define EAR_L 3
#define EAR_R 5

Servo earL;  // create servo object to control a servo
Servo earR;

unsigned long newTimeL, newTimeR;

const int maxServo = 110;
const int minServo = 70;
int polL = 90;
int polR = 90;
int vServo = 10;  // в миллисекундах задержка

int stepPin = 36;  // Пин к которому подключен D0
int motionDetected = 0;
int sensorVal = 0;
int napr = 1;

void setup() {
  Serial.begin(9600);
  earL.attach(EAR_L);  // attaches the servo on pin 9 to the servo object
  earR.attach(EAR_R);
  earL.write(polL);  // tell servo to go to position in variable 'pos'
  earR.write(polR);
  pinMode(stepPin, INPUT);  // Установим вывод A1 как вход
newTimeL = millis();
newTimeR = millis();
}

void loop() {
  motionDetected = digitalRead(stepPin);  // Считываем показания
  if (motionDetected)
    napr *= -1;
  if (napr > 0) {
    if (polR <= maxServo and newTimeR - millis() > vServo) {
      polR += 1;
      newTimeR = millis();
    }
    if (polL >= minServo and newTimeL - millis() > vServo) {
      polL -= 1;
      newTimeL = millis();
    }
  } else {
    if (polR >= minServo and newTimeR - millis() > vServo) {
      polR -= 1;
      newTimeR = millis();
    }
    if (polL <= maxServo and newTimeL - millis() > vServo) {}
    polL += 1;
    newTimeL = millis();
  }

earL.write(polL);
earR.write(polR);
}