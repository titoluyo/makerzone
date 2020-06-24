#ifndef MQTTConn_h
#define MQTTConn_h

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <PubSubClient.h>

class MQTTConn
{
private:
  WiFiClient espClient;
  PubSubClient client;
  const char* inTopic;
  const char* outTopic;
  long value = 0;
  void reconnect();
public:
  MQTTConn(const char * pinTopic, const char * poutTopic);
  ~MQTTConn();
  void setup(const char * domain, uint16_t port, MQTT_CALLBACK_SIGNATURE);
  void loop();
  void publish(const char* payload);
};

#endif
