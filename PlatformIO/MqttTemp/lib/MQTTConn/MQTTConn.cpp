#include "Arduino.h"
#include "MQTTConn.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

MQTTConn::MQTTConn(const char * pinTopic, const char * poutTopic)
{
  this->inTopic = pinTopic;
  this->outTopic = poutTopic;
  this->client = PubSubClient(espClient);
}

MQTTConn::~MQTTConn()
{
}


void MQTTConn::setup(const char * domain, uint16_t port, MQTT_CALLBACK_SIGNATURE) {
  this->client.setServer(domain, port);
  this->client.setCallback(callback);
}

void MQTTConn::reconnect() {
  // Loop until we're reconnected
  while (!this->client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (this->client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, resubscribe
      this->client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(this->client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MQTTConn::loop() {
  if(!this->client.connected()) {
    this->reconnect();
  }
  this->client.loop();
}

void MQTTConn::publish(const char* payload) {
  Serial.println(payload);
  this->client.publish(this->outTopic, payload);
}
