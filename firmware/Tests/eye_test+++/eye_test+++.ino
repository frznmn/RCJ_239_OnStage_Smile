n#include <Servo.h>
Servo myservo;

int pos = 0;
int pos2 = 0;

void setup() {
  myservo.attach(11);

}

void left(){
  for (pos = 0; pos <= 350; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15 ms for the servo to reach the position
  }
}

void right(){
  for (pos = 340; pos >= 240; pos -= 2) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15 ms for the servo to reach the position
  }//*/
}


void up(){
  for (pos = 0; pos <= 1800; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
void setup()
{
  Serial.begin(9600);
  pinMode(13,1);
}

void loop()
{
  char temp = "";
  if (Serial.available() > 0)
    temp = Serial.read();
    
  if(temp == "I")
    digitalWrite(13, 1);
    
  if(temp == "O")
    digitalWrite(13, 0); 
}
void down(){
  for (pos = 1; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }//*/
}

float posit = 0;
float angle = 0;
float kposit = 1, kangle = 0.25, err_posit, u_posit, u_angle;
int des_posit = 4;

void face(){
  //ne vazhno chto u nas vse na raznih arduino, sdelaem vid chto vse tak i dolzhno bit
 // u_posit = (posit - des_posit) * kposit;  
 myservo.write(posit);//?????????????????
    
}

void loop() {
  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
    }//*/
  left();
  right();

}
