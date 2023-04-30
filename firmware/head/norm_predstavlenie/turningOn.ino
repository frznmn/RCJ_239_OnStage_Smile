void turningOn() {
  if (ifTurningOn) {
    ifTurningOn = 0;
    newTimeL = millis();
    newTimeR = millis();
    timeTurningOn = millis();
  }
  for (int i = 3; i <= 9; i++) {
    eyeL.setPixelColor(i, eyeL.Color(0, 255, 0));  // включаем белый цвет на 3 светодиоде
    eyeR.setPixelColor(i, eyeR.Color(0, 255, 0));
    mouth.setPixelColor(i, mouth.Color(0, 255, 0));
  }
  eyeL.show();  // отправляем сигнал на ленту
  eyeR.show();
  mouth.show();

  delay(2000);
  c = 0;
  eyeL.clear();
  eyeR.clear();
  mouth.clear();
}