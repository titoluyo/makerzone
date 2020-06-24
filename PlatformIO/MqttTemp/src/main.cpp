#include <Arduino.h>
#include <WiFiConn.h>
#include <MQTTConn.h>
#include <TempRead.h>
#include "config.h"

MQTTConn mqtt(MQTT_IN_TOPIC, MQTT_OUT_TOPIC);
unsigned long now;
unsigned long last = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    Serial.println("led ON");
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    Serial.println("led OFF");
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ok");
  setup_wifi(AP_SSID, AP_PASS);
  mqtt.setup(MQTT_SERVER, 1883, callback);
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
