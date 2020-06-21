#ifndef TempRead_h
#define TempRead_h

#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT22

void tempBegin();

void readTemp();

#endif