#include <Adafruit_NeoPixel.h>

#include "FastLED.h"
#define NUM_LEDS 16
#define LED_INPUT_PIN 3
#define LED_TYPE WS2812
#define BRIGHTNESS 100

// how to design leds
// effects: stacking, color increasement, comet
// state: rainbow, dot moving 1 side, dot moving 2 side, filling left-right
// final combo: https://www.youtube.com/watch?v=seG5tip6wBw
// comet: https://www.youtube.com/watch?v=yM5dY7K2KHM

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
int lastMillis = 0;
long interval = 500;
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<LED_TYPE, LED_INPUT_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

class Sweeper {
  int current_pos;
  int time_delay;
  int lastMillis;

public:
  Sweeper(float speed) {
    time_delay = 600 / speed; // ms
    lastMillis = 0;
    current_pos = 0;
  }
  void Update(CRGB color = CRGB::Blue) {
    if ((millis() - lastMillis) > time_delay) {
      if (current_pos > NUM_LEDS) {
        current_pos = 0;
      }
      leds[current_pos] += color;
      leds[current_pos - 1] = CRGB::Black;
      current_pos++;
      FastLED.show();
      lastMillis = millis();
    }
  }
};
Sweeper sweeper1(10);
Sweeper sweeper2(5);
void loop() {
  sweeper1.Update();
  sweeper2.Update(CRGB::Pink);
}

/* void rainbow() { */
/*   // FastLED's built-in rainbow generator */
/*   fill_rainbow(leds, NUM_LEDS, gHue, 7); */
/* } */

// add whiteness randomly
/* void addGlitter(fract8 chanceOfGlitter) { */
/*   if (random8() < chanceOfGlitter) { */
/*     leds[random16(NUM_LEDS)] += CRGB::White; */
/*   } */
/* } */
/*  */
/* // like glitter but diff color and fade (GREENISH) */
/* void confetti() { */
/*   // random colored speckles that blink in and fade smoothly */
/*   fadeToBlackBy(leds, NUM_LEDS, 10); */
/*   int pos = random16(NUM_LEDS); */
/*   leds[pos] += CHSV(gHue + random8(64), 200, 255); */
/* } */
/*  */
/* // a colored dot sweeping back and forth, with fading trails */
/* void sinelon() { */
/*  */
/*   fadeToBlackBy(leds, NUM_LEDS, 20); */
/*   int pos = beatsin16(13, 0, NUM_LEDS - 1); */
/*   leds[pos] += CHSV(gHue, 255, 192); */
/* } */
/*  */
/* void bpm() { */
/*   // colored stripes pulsing at a defined Beats-Per-Minute (BPM) */
/*   uint8_t BeatsPerMinute = 62; */
/*   CRGBPalette16 palette = PartyColors_p; */
/*   uint8_t beat = beatsin8(BeatsPerMinute, 64, 255); */
/*   for (int i = 0; i < NUM_LEDS; i++) { // 9948 */
/*     leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i *
 * 10)); */
/*   } */
/* } */
/*  */
/* void juggle() { */
/*   // eight colored dots, weaving in and out of sync with each other */
/*   fadeToBlackBy(leds, NUM_LEDS, 20); */
/*   uint8_t dothue = 0; */
/*   for (int i = 0; i < 8; i++) { */
/*     leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255); */
/*     dothue += 32; */
/*   } */
/* } */
