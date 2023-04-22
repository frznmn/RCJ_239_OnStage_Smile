void CuteEars() {
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