#include <FastLED.h>
#include <TimerOne.h>

// FastLED setup
#define COLOR_CODE RGB
#define CHIPSET WS2812

const int numLEDs = 6;
const int dataPin = 3;
#define MIC_PIN A0                  // Analog port for microphone
uint8_t squelch = 1;                // Anything below this is background noise. Use a higher value with a physical microphone.
int sample;                         // Current sample.
float sampleAvg = 0;                // Smoothed Average.
float micLev = 0;                   // Used to convert returned value to have '0' as minimum.

int sampleAgc;                      // Automatic Gain Controlled value.
int magnitude;
int multAgc;                        // Multiplier for the AGC.
uint8_t targetAgc = 70;             // This is our setPoint at 20% of max for the adjusted output.

// LEDs' data
CRGB leds[numLEDs];
const int brightness        = 200;
const int redInitial        = 2;
const int greenInitial      = 204;
const int blueInitial       = 190;
const int colorIncrement    = 2;
const CRGB palette[numLEDs] = {
  {255, 25, 60}, {.r = 255, .g = 42, .b = 9}, {21, 20, 255},
  {10, 255, 0}, {60, 35, 255}, {0, 0, 0}
};
/* const CRGB palette[numLEDs] = {
  {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}
}; */
const CRGB initialColor = {redInitial, greenInitial, blueInitial};

void setup() {
  // Serial.begin(115200);
  FastLED.addLeds<CHIPSET, dataPin, COLOR_CODE>(leds, numLEDs);
  FastLED.setBrightness(brightness);
  // singleLEDColorSetup();
  // oneColorSetup();
  // chasingLEDSetup();
  // colorPaletteSetup();
  // chasingInterruptSetup(500000); // use if want chasing led effect at some specified interval
  FastLED.show();
  delay(20);
}

void loop() {
  // singleLEDColor();
  // chasingLED();
  // colorPaletteRotate();

  // one of these three getMagnitudeX functions must be used with all magnitude related functions
  // getMagnitudeFixed();
  getMagnitudeFixed2();
  // getMagnitudeAPC();

  // magnitudeBrightness();
  magnitudeLEDsSingle();
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

// ALL LED SAME COLOR
void oneColorSetup() {
  for (int i = 0; i < numLEDs; i++) {
    leds[i] = initialColor;
  }
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

void chasingLED() {
  rotate();
  FastLED.show();
  delay(20);
}

void rotate() {
  // naive but general approach - set each LED to the value of the previous
  // for chasingLED specific, given the offset, can just take the absolute
  // value of the current value minus (255 - colorOffset) to achieve the
  // same affect
  // forwards
  // Serial.println("rotate");
  // delay(10);
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
}

// COLOR PALETTE

void colorPaletteSetup() {
  for (int i = 0; i < numLEDs; i++) {
    leds[i] = palette[i];
  }
}

void colorPaletteRotate() {
  rotate();
  FastLED.show();
  delay(10);
}

// MAGNITUDE

void chasingInterruptSetup(unsigned long microseconds) {
  Timer1.initialize(microseconds);
  Timer1.attachInterrupt(chasingLED);
  delay(100);
}

void getMagnitudeFixed() {
  magnitude = map(analogRead(MIC_PIN), 0, 1023, 0, 255);
  // Serial.println(magnitude);
}

void getMagnitudeFixed2() {
  const int noiseLevel = 512;
  const int micIn = analogRead(MIC_PIN) - noiseLevel;
  magnitude = constrain(map(abs(micIn), 0, 512, 0, 255)*8 + 255/numLEDs, 0, 255);
  // Serial.print("magnitude: ");Serial.print(magnitude);

}

void getMagnitudeAPC() {
  getSample();
  agcAvg();
}

void magnitudeBrightness() {
  FastLED.setBrightness(map(magnitude, 0, 255, 60, 255));
  FastLED.show();
  delay(20);
}

void magnitudeLEDsSingle() {
  byte numLEDS = map(magnitude, 0, 255, 0, numLEDs);
  // Serial.print("\tnumLEDS: ");Serial.println(numLEDS);
  for (int i = 0; i < numLEDS; i++) {
    leds[i] = initialColor;
  }
  for (int i = numLEDS; i < numLEDs; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(20);
}

void getSample() {
  int16_t micIn;                                              // Current sample starts with negative values and large values, which is why it's 16 bit signed.

  micIn = analogRead(MIC_PIN);                                // Poor man's analog read.
  // Serial.print("\togMicIn: "); Serial.println(micIn);
  delay(20);
  micLev = ((micLev * 31) + micIn) / 32;                      // Use exponential smoothing over the last 32 samples for automatic centering.
  micIn -= micLev;                                            // Let's center it to 0. This allows us to use ANY microphone without having to worry about offset calculations.
  micIn = abs(micIn);                                         // And get the absolute value of each sample.

  sample = (micIn <= squelch) ? 0 : (sample + micIn) / 2;     // Let's filter out the background noise with a ternary operator and more exponential smoothing.
  sampleAvg = ((sampleAvg * 31) + sample) / 32;               // Smooth it out over the last 32 samples. This is a non AGC average.
  // Serial.print("micIn: "); Serial.print(micIn);
  // Serial.print("\tsample: "); Serial.print(sample);
  // Serial.print("\tsampleAvg: "); Serial.print(sampleAvg);
} // getSample()

void agcAvg() {                                                   // A simple averaging multiplier to automatically adjust sound sensitivity.
  multAgc = (sampleAvg < 1) ? targetAgc : targetAgc / sampleAvg;  // Make the multiplier so that sampleAvg * multiplier = setpoint
  sampleAgc = sample * multAgc;
  if (sampleAgc > 255) sampleAgc = 255;
  magnitude = sampleAgc;
  // Serial.print("\tmultAgc: "); Serial.print(multAgc);
  // Serial.print("\tsampleAgc: "); Serial.println(sampleAgc);
  // delay(20);
} // agcAvg()