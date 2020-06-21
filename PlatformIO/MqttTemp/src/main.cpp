#include <Arduino.h>
#include <WiFiConn.h>
#include <MQTTConn.h>
#include <TempRead.h>
#include "config.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Ok");
  setup_wifi(AP_SSID, AP_PASS);
  setup_MQTT(MQTT_SERVER, 1883, MQTT_IN_TOPIC, MQTT_OUT_TOPIC);
  tempBegin();
}

void loop() {
  mqtt_loop();
  readTemp();
  const char* msg = getMessage();
  publish(msg);
}
