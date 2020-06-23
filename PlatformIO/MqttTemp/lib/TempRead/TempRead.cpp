#include "TempRead.h"

DHT dht(DHTPIN, DHTTYPE);
char msgTemp[MSG_BUFFER_SIZE];

void tempBegin() {
  dht.begin();
}

const char* readTemp() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(false);
  if (isnan(h) || isnan(t)) {
    Serial.println("Impossible to read DHT!");
    return "";
  }
  snprintf (msgTemp, MSG_BUFFER_SIZE, "H:%1f,T%2fC", h, t);
  Serial.println(msgTemp);
  return msgTemp;
}
