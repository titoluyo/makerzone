#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN 9
#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);
int joystick[2];

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop()
{
  joystick[0] = analogRead(JOYSTICK_X);
  joystick[1] = analogRead(JOYSTICK_Y);
  Serial.print(joystick[0]);
  Serial.print("|");
  Serial.println(joystick[1]);
  radio.write( joystick, sizeof(joystick) );
}
