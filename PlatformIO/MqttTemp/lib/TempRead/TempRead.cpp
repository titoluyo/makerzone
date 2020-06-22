#include "TempRead.h"

DHT dht(DHTPIN, DHTTYPE);

unsigned long nowTemp;
unsigned long lastTemp = 0;
char msgTemp[MSG_BUFFER_SIZE];

void tempBegin() {
  dht.begin();
}

const char* readTemp() {
  nowTemp = millis();
  snprintf (msgTemp, MSG_BUFFER_SIZE, "");
  if (nowTemp - lastTemp > 2000) {
    lastTemp = nowTemp;
    float h = dht.readHumidity();
    float t = dht.readTemperature(false);
    if (isnan(h) || isnan(t)) {
      Serial.println("Impossible to read DHT!");
      return msgTemp;
    }
    snprintf (msgTemp, MSG_BUFFER_SIZE, "H:%1f,T%2fC", h, t);
    /*
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    */
   Serial.println(msgTemp);
  }
   return msgTemp;
}
