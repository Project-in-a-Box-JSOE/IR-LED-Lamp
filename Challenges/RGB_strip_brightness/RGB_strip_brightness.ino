#include <FastLED.h>

// FastLED setup
#define NUM_LEDS 6
#define DATA_PIN 3
#define COLOR_CODE RGB
#define CHIPSET WS2812

// LEDs' data
CRGB leds[NUM_LEDS];
int brightness = 0;
const int brightnessIncrement = 20;

void setup() {
    FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_CODE>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

void loop() {
    // increase constantly jumping to low from max
    brightness = (brightness + brightnessIncrement) % 255;

    // increase and decrease
    // for (int i = 0; i < ceil(255/brightness); i++) {
    //     brightness = constrain(brightness + brightnessIncrement, 0, 255);
    // }
    // for (int i = 0; i < ceil(255/brightness); i++) {
    //     brightness = constrain(brightness - brightnessIncrement, 0, 255);)
    // }

    // random
    // **NOTE: seed the random generator with an unused analog pin in setup
    // brightness = random(256); // min is 0 by default, max (256) is exclusive
}

/* 
#include <FastLED.h>

// FastLED setup
#define NUM_LEDS 6;
#define DATA_PIN 3;
#define COLOR_CODE RGB
#define CHIPSET WS2812

// LEDs' data
CRGB leds[NUM_LEDS];
int brightness = 42;
const int brightnessIncrement = 20;

void setup() {
    FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_CODE>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

void loop() {
    brightness = (brightness + brightnessIncrement) % 255;
}
 */
