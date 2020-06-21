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
  //PubSubClient client(espClient);
  const char* inTopic;
  const char* outTopic;
  unsigned long nowMqtt;
  unsigned long lastMqtt = 0;
  long value = 0;
  #define MSG_BUFFER_SIZE	(50)
  char msg[MSG_BUFFER_SIZE];
public:
  MQTTConn(/* args */);
  ~MQTTConn();
  void callback(char* topic, byte* payload, unsigned int length);
  void setup(const char * domain, uint16_t port, const char * pinTopic, const char * poutTopic);
  void reconnect();
  void mqtt_loop();
  const char* getMessage();
  void publish(const char* payload);
};

#endif
