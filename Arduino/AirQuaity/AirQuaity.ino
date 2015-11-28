#include "Sensor.h"
#include <DHT.h>
#include "TempHum.h"
#include "Mq2.h"
#include "Adafruit_FONA.h"
#include <SoftwareSerial.h>
#include "Sim.h"

#define SENSOR_PIN 6

Sim *sim = new Sim(3, 2, 4, 5);
Sensor* sensor[5];


unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned int interval = 20000; // envia datos al server cada 20seg

void Mensaje(char *msg){
  Serial.println(msg);
}

void Mensaje(const __FlashStringHelper* msg){
  Serial.println(msg);
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}

String valoresSensores[3];
void sendDataServer() {
  valoresSensores[0] = sensor[0]->getValue(0);
  valoresSensores[1] = sensor[0]->getValue(1);
  valoresSensores[2] = sensor[1]->getValue(0); //valor del sensor gas
  String trama = sim->construyeTrama(valoresSensores);
  //trama += char(13);
  trama += char(10);
  Serial.println(trama);
  char tramac[trama.length()+1];
  trama.toCharArray(tramac,sizeof(tramac));
  sim->sendData("162.243.69.120",8989,tramac, trama.length()+1);
}


void setup() {
  Serial.begin(115200);
  Mensaje("Instanciando temperatura");
  sensor[0] = new TempHum(SENSOR_PIN);
  sensor[1] = new Mq2(A2);
  Mensaje("sensor.setup");
  sensor[0]->setup();
  sensor[1]->setup();

  sim->setup();
}


char c1;
char c2;
char gpsdata[120];
void loop() {
  
  sensor[0]->sense();
  sensor[1]->sense();

  interactivo(); // solo para interactuar con el SerialMonitor
  
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    Serial.println(currentMillis - previousMillis);
    sendDataServer();
    previousMillis = currentMillis;
  }
}

void interactivo() {
  if(Serial.available()){
    c2 = Serial.read();
    switch (c2) {
      // SENSORES
      case '0': {
        Serial.print(sensor[0]->getValue(0));   //DHT22
        Serial.print(sensor[0]->getValue(1));   //DHT22
        Serial.print(sensor[0]->getValue(2)); //DHT22
        Serial.print(",");
        Serial.println(sensor[1]->getValue(0)); // MQ2
        break;
      }
      // GPSDATA
      case '1': {
        char gpsdata[120];
        sim->getGPSvalores(0, gpsdata, 120);
        Serial.println(gpsdata);
        break;
      }
      // TIEMPO
      case '2': {
        //Get Time
        char buffer[23];
        sim->getTime(buffer, 23);
        Serial.print(F("Time = ")); Serial.println(buffer);
        break;
      }
      // NIVEL DE BATERIA
      case '3': {
        uint16_t vbat;
        if (! sim->getBattPercent(&vbat)) {
          Serial.println(F("Failed to read Batt"));
        } else {
          Serial.print(F("VPct = ")); Serial.print(vbat); Serial.println(F("%"));
        }
        break;
      }
      /*
      case '4':
        //GSM Location
        uint16_t returncode;
        if (!fona->getGSMLoc(&returncode, replybuffer, 250))
          Serial.println(F("Failed!"));
        if (returncode == 0) {
          Serial.println(replybuffer);
        } else {
          Serial.print(F("Fail code #")); Serial.println(returncode);
        }
        break;
        */
    }
  }
}


