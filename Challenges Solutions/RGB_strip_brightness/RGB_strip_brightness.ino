#include <FastLED.h>

// FastLED setup
#define COLOR_CODE RGB
#define CHIPSET WS2812

const int numLEDs = 6;
const int dataPin = 3;

// LEDs' data
CRGB leds[numLEDs];
int brightness = 0;
const int brightnessIncrement = 20;

void setup() {
    FastLED.addLeds<CHIPSET, dataPin, COLOR_CODE>(leds, numLEDs);
    FastLED.setBrightness(brightness);
    leds[0] = CRGB::Green;
}

void loop() {
    // increase constantly jumping to low from max
    brightness = (brightness + brightnessIncrement) % 255;

    // increase and decrease
    // for (int i = 0; i < ceil(255/brightness); i++) {
    //     brightness = constrain(brightness + brightnessIncrement, 0, 255);
    //     FastLED.setBrightness(brightness);
    // }
    // for (int i = 0; i < ceil(255/brightness); i++) {
    //     brightness = constrain(brightness - brightnessIncrement, 0, 255);
    //     FastLED.setBrightness(brightness);
    // }

    // random
    // **NOTE: seed the random generator with an unused analog pin in setup
    // brightness = random(256); // min is 0 by default, max (256) is exclusive
    // FastLED.setBrightness(brightness);
}
