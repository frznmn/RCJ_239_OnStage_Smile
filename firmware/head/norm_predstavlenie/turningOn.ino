void turningOn(int x) {
  
      for (int i = 3; i <= 9; i++) {
        eyeL.setPixelColor(i, eyeL.Color(0, 255, 0));  // включаем белый цвет на 3 светодиоде
        eyeR.setPixelColor(i, eyeR.Color(0, 255, 0));
        mouth.setPixelColor(i, mouth.Color(0, 255, 0));
      }
      eyeL.show();  // отправляем сигнал на ленту
      eyeR.show();
      mouth.show();
    
  //  motionDetected = digitalRead(pinD0);  // Считываем показания
  // if (motionDetected) {
  //   naprav *= -1;
  //   if (naprav > 0) {
  //     for (int i = 70; i < 110; i++) {
  //       earL.write(i);  // tell servo to go to position in variable 'pos'
  //       earR.write(i);
  //       delay(5);
  //     }
  //   } else {
  //     for (int i = 110; i > 70; i--) {
  //       earL.write(i);  // tell servo to go to position in variable 'pos'
  //       earR.write(i);
  //       delay(5);
  //     }
  //   }
  // }
  // delay(2000);
  // c = 0;
  // eyeL.clear();
  // eyeR.clear();
  // mouth.clear();
}