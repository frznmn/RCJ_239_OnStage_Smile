#include <Stepper.h>  // библиотека для шагового двигателя

// количество шагов на 1 оборот, измените значение для вашего мотора
int stepsPerRevolution = 20;

// устанавливаем порты для подключения драйвера
Stepper myStepper(stepsPerRevolution, 37, 46, 45, 44);

void setup() {
  myStepper.setSpeed(255);  // устанавливаем скорость 60 об/мин
}

void loop() {
  // поворачиваем ротор по часовой стрелке
  myStepper.step(stepsPerRevolution);
  delay(100);
  //поворачиваем ротор против часовой стрелки
  myStepper.step(-stepsPerRevolution);
  delay(100);
}