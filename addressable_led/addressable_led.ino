#include "FastLED.h"
#define LED_PIN     7
#define NUM_LEDS    60

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void circle(int red, int green, int blue) {
  for (int i = 0;i < NUM_LEDS;i++) {
    leds[i] = CRGB(red, green, blue);
    for (int j = 0; j <= 8; j++){
      int index = (NUM_LEDS + i - j)%NUM_LEDS;
      leds[] = CRGB(red >> j, green >> j, blue >> j);
    }
    FastLED.show();
    delay(50);
  }
}

void loop() {
  circle(255,0,255);
}
