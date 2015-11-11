#include "Arduino.h"
#include "Sensor.h"

// Constructor con un solo pin
Sensor::Sensor(int pin) {
  _pin = pin;
}

// Constructor con dos pines
Sensor::Sensor(int pin, int pin2) {
  _pin = pin;
  _pin2 = pin2;
}

// A ejecutarse en la seccion de setup
void Sensor::setup() {}

// A sensar
void Sensor::sense() {}

void Sensor::sense2() {}

// Obtener el valor actual del sensor
char* Sensor::getValue(int index) {}

// Obtener el valor actual del sensor
char* Sensor::getValue2(String title) {
  s = "|" + title + ":" + s;
  s.toCharArray(c,sizeof(c));
  return c;
}

// Obtener la cantidad de valores obtenidos del sensor
int Sensor::getCantidadValores() {
  return _cantidadValores;
}

