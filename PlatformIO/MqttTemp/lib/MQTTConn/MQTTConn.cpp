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

void MQTTConn::setup(const char * domain, uint16_t port) {
  pinMode(LED_BUILTIN, OUTPUT);
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
  Serial.println(this->outTopic);
  Serial.println(payload);
  this->client.publish(this->outTopic, payload);
}
