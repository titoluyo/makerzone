#include "Sensor.h"
#include <DHT.h>
#include "TempHum.h"
#include "Adafruit_FONA.h"
#include <SoftwareSerial.h>

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4
#define FONA_PWR 5

#define SENSOR_PIN 6

// this is a large buffer for replies
char replybuffer[255];

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

Sensor* sensor[5];

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

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


void setup() {
  Serial.begin(115200);
  Mensaje("Instanciando temperatura");
  sensor[0] = new TempHum(SENSOR_PIN);
  Mensaje("sensor.setup");
  sensor[0]->setup();

  Serial.println("Iniciando...");

  pinMode(FONA_PWR, OUTPUT);
  Serial.println(F("Apagando"));
  digitalWrite(FONA_PWR, HIGH);
  delay(2200);
  digitalWrite(FONA_PWR, LOW);
  delay(2200);
  Serial.println(F("Prendiendo"));
  digitalWrite(FONA_PWR, HIGH);
  delay(2200);
  digitalWrite(FONA_PWR, LOW);
  delay(2200);

  Serial.println("Reiniciando FONA");
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Mensaje(F("Couldn't find FONA"));
    while (1);
  }

  Serial.println("Registrando APN");
  fona.setGPRSNetworkSettings(F("movistar.pe"), F("movistar@datos"), F("movistar"));
  delay(5000);

  Serial.println("Habilitando Datos");
  if (!fona.enableGPRS(true))
    Mensaje(F("Failed to turn on Data"));
  delay(5000);

  Serial.println("Habilitando GPS");
  if (!fona.enableGPS(true))
    Mensaje(F("Failed to turn on GPS"));
  delay(5000);

  Serial.println("Habilitando tiempo GSM");
  if (!fona.enableNetworkTimeSync(true))
    Serial.println(F("Failed to enable tiempo GSM"));
  delay(5000);

  Serial.println("Habilitando tiempo NTP");
  if (!fona.enableNTPTimeSync(true, F("pool.ntp.org")))
    Serial.println(F("Failed to enable NTP"));
  delay(5000);


  //GPS Status
  int8_t stat = -1;
  while (stat < 2) {
    // check GPS fix
    stat = fona.GPSstatus();
    if (stat < 0)
      Serial.println(F("Failed to query"));
    if (stat == 0) Serial.println(F("GPS off"));
    if (stat == 1) Serial.println(F("No fix"));
    if (stat == 2) Serial.println(F("2D fix"));
    if (stat == 3) Serial.println(F("3D fix"));
    delay(1000);
  }

}

char c1;
char c2;
char gpsdata[120];
void loop() {
  
//  sensor[0]->sense();
  if(Serial.available()){
    c2 = Serial.read();
    switch (c2) {
      /*
      case '0':
        Serial.println(F("Desactivando"));
        fona.enableGPSNMEA(0);
        break;
      case '1':
        Serial.println(F("Reactivando"));
        fona.enableGPSNMEA(34);
        break;
      */
      /*
      case '2':
        Serial.print(sensor[0]->getValue(0));
        Serial.print(sensor[0]->getValue(1));
        Serial.println(sensor[0]->getValue(2));
        break;
      case '3':
        //Get Time
        char buffer[23];
        fona.getTime(buffer, 23);
        Serial.print(F("Time = ")); Serial.println(buffer);
        break;
      case '4':
        //GSM Location
        uint16_t returncode;
        if (!fona.getGSMLoc(&returncode, replybuffer, 250))
          Serial.println(F("Failed!"));
        if (returncode == 0) {
          Serial.println(replybuffer);
        } else {
          Serial.print(F("Fail code #")); Serial.println(returncode);
        }
        break;
      */
      case 'x':
        fona.getGPS(0, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
      case '0':
        fona.getGPS(1, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
      case '1':
        fona.getGPS(2, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
      case '2':
        fona.getGPS(4, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
      case '3':
        fona.getGPS(8, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
      case '4':
        fona.getGPS(16, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
      case '5':
        fona.getGPS(32, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
      case '6':
        fona.getGPS(64, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
      case '7':
        fona.getGPS(128, gpsdata, 120);
        Serial.println(gpsdata);
        break;        
    }

  }
}

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout) {
  uint16_t buffidx = 0;
  boolean timeoutvalid = true;
  if (timeout == 0) timeoutvalid = false;

  while (true) {
    if (buffidx > maxbuff) {
      //Serial.println(F("SPACE"));
      break;
    }

    while (Serial.available()) {
      char c =  Serial.read();

      //Serial.print(c, HEX); Serial.print("#"); Serial.println(c);

      if (c == '\r') continue;
      if (c == 0xA) {
        if (buffidx == 0)   // the first 0x0A is ignored
          continue;

        timeout = 0;         // the second 0x0A is the end of the line
        timeoutvalid = true;
        break;
      }
      buff[buffidx] = c;
      buffidx++;
    }

    if (timeoutvalid && timeout == 0) {
      //Serial.println(F("TIMEOUT"));
      break;
    }
    delay(1);
  }
  buff[buffidx] = 0;  // null term
  return buffidx;
}




