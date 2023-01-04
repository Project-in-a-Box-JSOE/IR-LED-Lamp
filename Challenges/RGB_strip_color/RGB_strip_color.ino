#include <FastLED.h>

// FastLED setup
#define NUM_LEDS 6
#define DATA_PIN 3
#define COLOR_CODE RGB
#define CHIPSET WS2812

// LEDs' data
CRGB leds[NUM_LEDS];
const int brightness        = 200;
const int redInitial        = 2;
const int greenInitial      = 204;
const int blueInitial       = 190;
const int colorIncrement    = 2;
const CRGB palette[NUM_LEDS]= {
    {120, 25, 90}, {.r = 144, .g = 42, .b = 9}, {21, 20, 95},
    {10, 190, 72}, {100, 35, 90}
};

void setup() {
    FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_CODE>(leds, NUM_LEDS);
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
    for (int i = 0; i < NUM_LEDS; i++) {
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
    for (int i = 0; i < NUM_LEDS - 1; i++) {
      leds[i] = leds[i + 1];
    }
    leds[NUM_LEDS - 1] = firstLED;

    // backwards
    /*CRGB lastLED = leds[NUM_LEDS-1];
    for (int i = NUM_LEDS - 1; i > 0; i--) {
        leds[i] = leds[i-1];
    }
    leds[0] = lastLED;*/
    
    FastLED.show();
    delay(125);
}

// COLOR PALETTE

void colorPaletteSetup() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = palette[i];
    }
}