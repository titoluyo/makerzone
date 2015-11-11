#include <Adafruit_NeoPixel.h>
//#include "WS2812_Definitions.h"

#define PIN 6
#define LED_COUNT 300

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  leds.begin();
  clearLEDs();
  leds.show();
  randomSeed(analogRead(0));
}

void loop() {
  uint32_t color = 0x050505;
  uint8_t r, g, b;
  for (int i=0; i < LED_COUNT; i++){
    for (int j=0; j < LED_COUNT; j++){
      r = random(64);
      g = random(64);
      b = random(64);
      //if(i == j) 
      color = leds.Color(r, g, b);
      //else color = 0x050505;
      leds.setPixelColor(j, color);
    }
    leds.show();
  }
}

void clearLEDs()
{
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0);
  }
}
