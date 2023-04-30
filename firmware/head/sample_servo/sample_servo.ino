#include <Servo.h>

#define EAR_L 3
#define EAR_R 5

Servo earL;  // create servo object to control a servo
Servo earR;

int pos = 0;    // variable to store the servo position

void setup() {
  earL.attach(EAR_L);  // attaches the servo on pin 9 to the servo object
  earR.attach(EAR_R);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    earL.write(pos);              // tell servo to go to position in variable 'pos'
    earR.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    earR.write(pos);              // tell servo to go to position in variable 'pos'
    earL.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
