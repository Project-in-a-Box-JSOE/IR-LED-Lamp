#include <FastLED.h>

// FastLED setup
#define COLOR_CODE GRB  // The order of colors (if using hex for ex.)
#define CHIPSET WS2812  // The LEDS in this strip are WS2812

const int numLeds = _;  // The number of LEDS on the strip
const int dataPin = _;  // The pin the LED strip is connected to

// LEDs' data
CRGB leds[numLEDs];
const int brightness        = ___;
const int redInitial        = ___;
const int greenInitial      = ___;
const int blueInitial       = ___;
const int colorIncrement    = _;
const CRGB palette[numLEDs]= {
  {255, 25, 60}, {255, 42, 9}, {21, 20, 255},
  {10, 255, 0}, {60, 35, 255}, {0, 0, 0}
};

void setup() {
    FastLED.addLeds<CHIPSET, dataPin, COLOR_CODE>(leds, numLEDs);
    FastLED.setBrightness(brightness);
    // uncomment these as you finish your functions
    // singleLEDColorSetup();
    // chasingLEDSetup();
    // colorPaletteSetup();
    FastLED.show();
}

void loop() {
    // uncomment these as you finish your functions
    // singleLEDColor();
    // rotate();
    FastLED.show();
    delay(10);
}

// SINGLE LED COLOR
void singleLEDColorSetup() {
    // set each color to the initial color defined at the top
    leds[0].r = ____;
    leds[0].g = ____;
    leds[0].b = ____;
}

void singleLEDColor() {
    // cycle through colors of the first LED
    // TODO
    FastLED.show();
    delay(10);
}

// Chasing LED
void chasingLEDSetup() {
    
}

void rotate() {
    
}

// COLOR PALETTE
void colorPaletteSetup() {
}