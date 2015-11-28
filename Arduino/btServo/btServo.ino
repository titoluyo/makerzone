#include <LiquidCrystal.h>
#include <Servo.h> 
#include <SoftwareSerial.h>

SoftwareSerial Genotronex(11, 12); // RX, TX
Servo myservoMa;
int posMa = 120;
int incMa = 0;
String data = "";
int incoming = 0;

void setup() {
  Genotronex.begin(9600);
  Serial.begin(9600);
  myservoMa.attach(10);
}

void loop() {
  if (Genotronex.available()){
      char character = Genotronex.read();
      data.concat(character);
      if (character == '\n'){
        Serial.println(data);
        incoming = data.toInt();
        data = "";
        
        myservoMa.write(incoming);
        delay(15);
      }
  }      
}
