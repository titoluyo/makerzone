#ifndef WiFiConn_h
#define WiFiConn_h

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

void setup_wifi(const char* ssid, const char *passphrase);

#endif