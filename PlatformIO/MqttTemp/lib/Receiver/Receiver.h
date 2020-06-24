#ifndef Receiver_h
#define Receiver_h

#include <Arduino.h>

void callback(char* topic, byte* payload, unsigned int length);

#endif