#include "Receiver.h"
#include <Arduino.h>

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  char command[length];

  for (unsigned int i = 0; i < length; i++) {
    char curr = (char)payload[i];
    command[i] = curr;
  }
  Serial.println(command);
}