/*
Sensor DHT22
Sensor de Temperature y humedad
*/
#include "Arduino.h"
#include <DHT.h>
#include "TempHum.h"

TempHum::TempHum(int pin) : Sensor(pin) {
  _cantidadValores = CANTIDAD_VALORES;
  _title[0] = "H";
  _title[1] = "T";
  _title[2] = "HT";
  _previousMillis = 0;
  _interval = 2000;
}

void TempHum::setup() {
	_dht = new DHT(_pin, DHT22);
  _dht->begin();
}

void TempHum::sense() {
  _currentMillis = millis();
  if (_currentMillis - _previousMillis <= _interval) return;
	sense2();
  _previousMillis = _currentMillis;
}

void TempHum::sense2(){
  float h = _dht->readHumidity();
  float t = _dht->readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float hic = _dht->computeHeatIndex(t, h, false);
  _val[0] = h;
  _val[1] = t;
  _val[2] = hic;
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.println(" *C ");
}

// Obtener el valor actual del sensor
char* TempHum::getValue(int index) 
{
  s = String(_val[index],2);
  return getValue2(_title[index]);
  /*
  s = "|" + _title[index] + ":" + s;
  s.toCharArray(c,sizeof(c));
  return c;
  */
}


