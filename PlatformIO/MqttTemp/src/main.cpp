#include <Arduino.h>
#include <WiFiConn.h>
#include "config.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Ok");
  setup_wifi(AP_SSID, AP_PASS);
}

void loop() {
  // put your main code here, to run repeatedly:
}