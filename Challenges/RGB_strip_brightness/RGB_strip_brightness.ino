#include <FastLED.h>

// FastLED setup
#define COLOR_CODE RGB  // The order of colors (if using hex for ex.)
#define CHIPSET WS2812  // The LEDS in this strip are WS2812

const int numLeds = _;  // The number of LEDS on the strip
const int dataPin = _;  // The pin the LED strip is connected to

// LEDs' data
CRGB leds[numLeds];     // Initialize an array of the led colors to 0x000000 (black)
int brightness = 0;     // Start the LED off (0-255)
const int brightnessIncrement = 1; // Increments of the brightness increase

void setup() {
    FastLED.addLeds<CHIPSET, dataPin, COLOR_CODE>(leds, numLeds);   // Initialize the LED strip
    FastLED.setBrightness(brightness);  // Set the initial brightness of the strip
    leds[0] = CRGB::Green;  // Makes the first LED green (Ignore for now)
    FastLED.show();
}

void loop() {
    brightness = _____; // increase constantly jumping to low from max
    // TODO: Update brightness with FastLED (2 more lines suggested)
}
