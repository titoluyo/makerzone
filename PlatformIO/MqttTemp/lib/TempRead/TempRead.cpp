#include "TempRead.h"

DHT dht(DHTPIN, DHTTYPE);

unsigned long nowTemp;
unsigned long lastTemp = 0;

void tempBegin() {
  dht.begin();
}

void readTemp() {
  nowTemp = millis();
  if (nowTemp - lastTemp > 2000) {
    lastTemp = nowTemp;
    float h = dht.readHumidity();
    float t = dht.readTemperature(false);
    if (isnan(h) || isnan(t)) {
      Serial.println("Impossible de lire la sonde DHT!");
      return;
    }
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
  }
}
