#include <Arduino.h>
#include <WiFiConn.h>
#include <MQTTConn.h>
#include <TempRead.h>
#include "config.h"

MQTTConn mqtt(MQTT_IN_TOPIC, MQTT_OUT_TOPIC);
unsigned long now;
unsigned long last = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Ok");
  setup_wifi(AP_SSID, AP_PASS);
  mqtt.setup(MQTT_SERVER, 1883);
  tempBegin();
}

void loop() {
  mqtt.loop();
  now = millis();
  if (now - last > 2000) {
    last = now;
    mqtt.publish(readTemp());
  }
}
