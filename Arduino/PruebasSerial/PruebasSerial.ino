#include <Servo.h>

byte intBuffer[12];
String intData = "";
int delimiter = (int) '\n';
Servo servo[4];
int pins[] = {5, 6, 9, 10};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++){
    servo[i].attach(pins[i]);
    servo[i].write(0);
    delay(15);
  }
}

void loop() {
  while (Serial.available()){
    int pos = Serial.parseInt();
    for (int i = 0; i < 4; i++){
      if (i != 2) {      
        servo[i].write(pos);
      } else {
        servo[i].write(180-pos);      
      }
    }
  }
}
