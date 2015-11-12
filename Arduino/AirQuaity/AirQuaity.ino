#include "Sensor.h"
#include <DHT.h>
#include "TempHum.h"

Sensor* sensor[5];
void setup() {
  Serial.begin(115200);
  Serial.println("Instanciando temperatura");
  sensor[0] = new TempHum(5);
  Serial.println("sensor.setup");
  sensor[0]->setup();
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}

void loop() {
  sensor[0]->sense();
  if(Serial.available()){
    serialFlush();
    Serial.print(sensor[0]->getValue(0));
    Serial.print(sensor[0]->getValue(1));
    Serial.println(sensor[0]->getValue(2));
  }
}


