#include <FastLED.h>

// FastLED setup
#define COLOR_CODE GRB  // The order of colors (if using hex for ex.)
#define CHIPSET WS2812  // The LEDS in this strip are WS2812

const int numLEDs = 6;  // The number of LEDS on the strip
const int dataPin = 3;  // The pin the LED strip is connected to

// LEDs' data
CRGB leds[numLEDs];
const int brightness        = 40; // Set to a nonzero positive value (0 < brightness < 256)
const int redInitial        = __; // Initial amount of red light
const int greenInitial      = __; // Initial amount of green light
const int blueInitial       = __; // Initial amount of blue light
const int colorIncrement    = 1;  // Dependent on delay in loop
const CRGB palette[numLEDs] = {
  {255, 25, 60}, {255, 42, 9}, {21, 20, 255},
  {10, 255, 0}, {60, 35, 255}, {0, 0, 0}
};

enum Mode {singleLED, chasingLED, colorPalette};
Mode currentMode = singleLED;

void setup() {
  FastLED.addLeds<CHIPSET, dataPin, COLOR_CODE>(leds, numLEDs);
  FastLED.setBrightness(brightness);
  
  // Set up the leds with the desired initial color states
  switch (currentMode) {
    case singleLED:
      singleLEDColorSetup();
      break;
    case chasingLED:
      chasingLEDSetup();
      break;
    case colorPalette:
      colorPaletteSetup();
      break;
    default:
      break;
  }
  FastLED.show(); // Push the changes to the LED strip
  delay(10);
}

void loop() {
  // Call on the function that performs the lighting mode changes
  switch (currentMode) {
    case singleLED:
      singleLEDColor();
      break;
    case chasingLED:
      rotate();
      break;
    case colorPalette:
      rotate();
      break;
    default:
      break;
  }
  FastLED.show(); // Push the changes to the LED strip
  delay(10);
}

// SINGLE LED COLOR
void singleLEDColorSetup() {
  // set each color to the initial color defined at the top
  leds[0].r = redInitial;
  leds[0].g = greenInitial;
  leds[0].b = blueInitial;
}

void singleLEDColor() {
  // TODO: cycle through colors of the first LED
  // I recommend that you increment each color in different amounts
  leds[0].r = __;
  leds[0].g = __;
  leds[0].b = __;
}

// Chasing LED
void chasingLEDSetup() {
  // TODO
}

void rotate() {
  // TODO
}

// COLOR PALETTE
void colorPaletteSetup() {
  // TODO
}
