#include <Wire.h>                             // Подключаем библиотеку Wire
#include <SparkFun_APDS9960.h>                // Подключаем библиотеку SparkFun_APDS9960
 
#define APDS9960_INT  19                    // Указываем вывод прерывания
 
SparkFun_APDS9960 apds = SparkFun_APDS9960(); // Создаем объект
int isr_flag = 0;                             // Создаем переменную isr_flag
 
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
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
 
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}
 
void loop() {
  if( isr_flag == 1 ) {
    detachInterrupt(4);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(4, interruptRoutine, FALLING);
  }
}
 
void interruptRoutine() {
  isr_flag = 1;
}
 
void handleGesture() {
    if ( apds.isGestureAvailable() ) {
      // Serial.println("uuuu");
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}