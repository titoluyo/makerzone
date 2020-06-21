#ifndef MQTTConn_h
#define MQTTConn_h

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <PubSubClient.h>


void setup_MQTT(const char * domain, uint16_t port, const char * pinTopic, const char * poutTopic);

void mqtt_loop();

const char* getMessage();

void publish(const char* payload);

#endif
