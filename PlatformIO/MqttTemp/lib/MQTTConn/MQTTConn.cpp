#include "Arduino.h"
#include "MQTTConn.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

WiFiClient espClient;
PubSubClient client(espClient);
const char* inTopic;
const char* outTopic;
unsigned long nowMqtt;
unsigned long lastMqtt = 0;
long value = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

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


void setup_MQTT(const char * domain, uint16_t port, const char * pinTopic, const char * poutTopic) {
  inTopic = pinTopic;
  outTopic = poutTopic;
  pinMode(LED_BUILTIN, OUTPUT);
  client.setServer(domain, port);
  client.setCallback(callback);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqtt_loop() {
  nowMqtt = millis();

  if(!client.connected()) {
    reconnect();
  }
  client.loop();
}

const char* getMessage() {
  snprintf(msg, MSG_BUFFER_SIZE, "");
  if (nowMqtt - lastMqtt > 2000) {
    lastMqtt = nowMqtt;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
  }
  return msg;
}

void publish(const char* payload) {
    client.publish(outTopic, payload);
}
