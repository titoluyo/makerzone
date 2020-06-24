#ifndef TempRead_h
#define TempRead_h

#include <DHT.h>
#include <DHT_U.h>

// D4 -> 2
#define DHTPIN 2
#define DHTTYPE DHT22
#define MSG_BUFFER_SIZE	(50)

void tempBegin();

const char* readTemp();

#endif