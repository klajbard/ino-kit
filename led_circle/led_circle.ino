#include <Adafruit_NeoPixel.h>
 
#define PIN            2
#define NUM_LEDS      12
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void circle(int red, int green, int blue) {
  for (int i = 0;i < NUM_LEDS;i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
    pixels.show();
    for (int j = 0; j <= 8; j++){
      int index = (NUM_LEDS + i - j)%NUM_LEDS;
      pixels.setPixelColor(index, pixels.Color(red >> j, green >> j, blue >> j));
      pixels.show();
    }
    delay(50);
  }
}

int colors[][3] = {
  {255, 0, 0},
  {255, 128, 0},
  {255, 255, 0},
  {128, 255, 0},
  {0, 255, 0},
  {0, 255, 128},
  {0, 255, 255},
  {0, 128, 255},
  {0, 0, 255},
  {128, 0, 255},
  {255, 0, 255},
  {255, 0, 128},
};

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}
 
void loop() {
  int times = 10;
  circle(8,0,8);
  circle(8,0,0);
  circle(0,8,0);
  circle(0,0,8);
  while (times) {
    for (int i = 0; i < NUM_LEDS; i++) {
      for (int j = 0; j < NUM_LEDS; j++) {
        int index = (NUM_LEDS + j + i)%NUM_LEDS;
        pixels.setPixelColor(index, pixels.Color(colors[j][0], colors[j][1], colors[j][2]));
        pixels.show();
      }
      delay(50);
    }
    times--;
  }
  
  for (int j = 0; j < NUM_LEDS; j++) {
    pixels.setPixelColor(j, pixels.Color(colors[j][0], colors[j][1], colors[j][2]));
    pixels.show();
  }
  
  delay(100000);
}
