#include "Adafruit_FONA.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4
#define FONA_PWR 5

char replybuffer[255];

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

// The TinyGPS++ object
TinyGPSPlus gps;
long inicio;

void setup()
{
  Serial.begin(115200);
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

//  ss.begin(GPSBaud);
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

  if (!fona.enableGPS(true))
    Serial.println(F("Failed to turn on"));

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


  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();

  fona.enableGPSNMEA(34);
  inicio = millis();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (fona.available() > 0)
    if (gps.encode(fona.read()))
      displayInfo();

  if (Serial.available()) {
    char c = Serial.read();
    if (c == '0') {
      Serial.println(F("Desactivando"));
      fona.enableGPSNMEA(0);
    }
    if (c == '1') {
      Serial.println(F("Reactivando"));
      fona.enableGPSNMEA(34);
    }
  }

  if (millis() - inicio > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 5);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 5);
    Serial.print(F(" - "));
    Serial.print((gps.location.lat() * 100000), 0);
    Serial.print(F(","));
    Serial.print((gps.location.lng() * 100000), 0);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
