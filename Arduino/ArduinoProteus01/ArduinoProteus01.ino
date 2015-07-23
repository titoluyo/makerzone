#include <Servo.h>

const byte pinServo = 3;
Servo miServo;

void setup() {
  Serial.begin(9600);
  miServo.attach(pinServo);
}

void loop() {
  byte byteLeido;
  if(Serial.available() > 0) {
    byteLeido = Serial.read();
    miServo.write(byteLeido);
    Serial.print("Dato recibido:");
    Serial.println(byteLeido,DEC);
  }
  delay(100);
}
