#include "TempRead.h"

DHT_Unified dht(DHTPIN, DHTTYPE);
char msgTemp[MSG_BUFFER_SIZE];
float t, h;

void tempBegin() {
  dht.begin();

  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.

}

const char* readTemp() {
  sensors_event_t event;
  // Get temperature event
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    t = event.temperature;
  }
  // Get humidity event
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    h = event.relative_humidity;
  }
  snprintf (msgTemp, MSG_BUFFER_SIZE, "%4.2f|%4.2f", h, t);
  Serial.println(msgTemp);
  return msgTemp;
}
