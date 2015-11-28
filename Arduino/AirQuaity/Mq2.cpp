/*
Sensor MQ2
Sensor de gases
*/
#include "Arduino.h"
#include "Mq2.h"

Mq2::Mq2(int pin) : Sensor(pin) {
  _cantidadValores = CANTIDAD_VALORES;
  _title[0] = "G";
  _previousMillis = 0;
  _interval = 1000;
  _pin_a0 = pin;
}

void Mq2::setup() {
  pinMode(_pin_a0, INPUT);
}

void Mq2::sense() {
  _currentMillis = millis();
  if (_currentMillis - _previousMillis <= _interval) return;
  sense2();
  _previousMillis = _currentMillis;
}

void Mq2::sense2(){
  _val[0] = analogRead(_pin_a0);
  Serial.print("Gas: ");
  Serial.println(_val[0]);
}

// Obtener el valor actual del sensor
char* Mq2::getValue(int index) 
{
  s = String(_val[index],0);
  return getValue2(_title[index]);
  /*
  s = "|" + _title[index] + ":" + s;
  s.toCharArray(c,sizeof(c));
  return c;
  */
}


