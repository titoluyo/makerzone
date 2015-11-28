#include <Arduino.h>
#include "Adafruit_FONA.h"
#include <SoftwareSerial.h>


#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

void PowerToggle(int _pwr){
  pinMode(_pwr, OUTPUT);
  digitalWrite(_pwr, HIGH);
  delay(2200);
  digitalWrite(_pwr, LOW);
  delay(2200);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando");
  //PowerToggle(5);
}



void loop() {
  while(Serial.available()){
    char c = Serial.read();
    Serial.println(c);
    if(c=='1') {
      Serial.println("Powering");
    }
    if(c='2') {
      fonaSerial->begin(4800);
      if (! fona.begin(*fonaSerial)) {
        Serial.println(F("Couldn't find FONA"));
        while (1);
      }      
    }
  }

}
