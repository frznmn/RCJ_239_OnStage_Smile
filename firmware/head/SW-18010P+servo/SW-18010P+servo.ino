#include <Servo.h>

#define EAR_L 3
#define EAR_R 5

Servo earL;  // create servo object to control a servo
Servo earR;

const int maxServo = 110;
const int minServo = 70;
int polL = 90;
int polR = 90;
int vServo = 1; // в миллисекундах задержка

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
}

void loop() {
  motionDetected = digitalRead(stepPin);  // Считываем показания
  if (motionDetected)
    napr *= -1;
  if (napr > 0) {
    if (polR <= maxServo)
      polR += 1;
    if (polL >= minServo)
      polL -= 1;
  } else {
    if (polR >= minServo)
      polR -= 1;
    if (polL <= maxServo)
      polL += 1;
  }
  earL.write(polL);
  earR.write(polR);
}