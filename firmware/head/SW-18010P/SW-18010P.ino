#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define EAR_L 3
#define EAR_R 5

Servo earL;  // create servo object to control a servo
Servo earR;

Adafruit_NeoPixel mouth(15, 34, NEO_GRB + NEO_KHZ800);

int pinD0 = 36;  // Пин к которому подключен D0
int motionDetected = 0;
int sensorVal = 0;
int naprav = 1;

void setup() {
  Serial.begin(9600);
  // earL.attach(EAR_L);  // attaches the servo on pin 9 to the servo object
  // earR.attach(EAR_R);
  // earL.write(30);  // tell servo to go to position in variable 'pos'
  //       earR.write(170);
  pinMode(pinD0, INPUT);  // Установим вывод A1 как вход
  mouth.begin();            // инициализируем ленту
  mouth.setBrightness(30);
}

void loop() {
  motionDetected = digitalRead(pinD0);  // Считываем показания
  if (motionDetected) {
    for (int i = 0; i <= 15; i++) {
    mouth.setPixelColor(i, mouth.Color(102, 200, 255));
    }
        mouth.show();
    delay(100);}
    else{
      for (int i = 0; i <= 15; i++) {
    mouth.setPixelColor(i, mouth.Color(0, 0, 0));
    }
    }
 mouth.show();
  //   naprav *= -1;
  //   if (naprav > 0) {
  //     for (int i = 90; i < 120; i++) {
  //       earL.write(-i);  // tell servo to go to position in variable 'pos'
  //       earR.write(i);
  //       delay(5);
  //     }
  //   } else {
  //     for (int i = 90; i > -120; i--) {
  //       earL.write(-i);  // tell servo to go to position in variable 'pos'
  //       earR.write(i);
  //       delay(5);
  //     }
  //   }
  // }
}