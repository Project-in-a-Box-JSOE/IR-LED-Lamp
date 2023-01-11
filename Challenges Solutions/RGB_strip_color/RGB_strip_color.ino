#include <FastLED.h>

// FastLED setup
#define COLOR_CODE RGB
#define CHIPSET WS2812

const int numLEDs = 6;
const int dataPin = 3;

// LEDs' data
CRGB leds[numLEDs];
const int brightness        = 200;
const int redInitial        = 2;
const int greenInitial      = 204;
const int blueInitial       = 190;
const int colorIncrement    = 2;
const CRGB palette[numLEDs]= {
    {120, 25, 90}, {.r = 144, .g = 42, .b = 9}, {21, 20, 95},
    {10, 190, 72}, {100, 35, 90}
};

void setup() {
    FastLED.addLeds<CHIPSET, dataPin, COLOR_CODE>(leds, numLEDs);
    FastLED.setBrightness(brightness);
    // singleLEDColorSetup();
    // chasingLEDSetup();
    colorPaletteSetup();
    FastLED.show();
}

void loop() {
    
    // singleLEDColor();
    rotate();
}

// SINGLE LED COLOR
void singleLEDColorSetup() {
    leds[0].r = redInitial;
    leds[0].g = greenInitial;
    leds[0].b = blueInitial;
}

void singleLEDColor() {
    // single LED cycle through 
    leds[0].r = (leds[0].r + colorIncrement) % 255;
    leds[0].g = (leds[0].g + colorIncrement) % 255;
    leds[0].b = (leds[0].b + colorIncrement) % 255;
    FastLED.show();
    delay(10);
}

// Chasing LED

void chasingLEDSetup() {
    const int colorOffset = 42;
    for (int i = 0; i < numLEDs; i++) {
        leds[i].r = constrain(redInitial - colorOffset * i, 0, 255);
        leds[i].g = constrain(greenInitial - colorOffset * i, 0, 255);
        leds[i].b = constrain(blueInitial - colorOffset * i, 0, 255);
    }
}

void rotate() {
    // naive but general approach - set each LED to the value of the previous
    // for chasingLED specific, given the offset, can just take the absolute
    // value of the current value minus (255 - colorOffset) to achieve the
    // same affect
    // forwards
    CRGB firstLED = leds[0];
    for (int i = 0; i < numLEDs - 1; i++) {
      leds[i] = leds[i + 1];
    }
    leds[numLEDs - 1] = firstLED;

    // backwards
    /*CRGB lastLED = leds[numLEDs-1];
    for (int i = numLEDs - 1; i > 0; i--) {
        leds[i] = leds[i-1];
    }
    leds[0] = lastLED;*/
    
    FastLED.show();
    delay(125);
}

// COLOR PALETTE

void colorPaletteSetup() {
    for (int i = 0; i < numLEDs; i++) {
        leds[i] = palette[i];
    }
}