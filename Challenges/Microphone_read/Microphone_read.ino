#include <FastLED.h>
#include <TimerOne.h>

// FastLED setup
#define COLOR_CODE GRB  // The order of colors (if using hex for ex.)
#define CHIPSET WS2812  // The LEDS in this strip are WS2812
#define MIC_PIN A0                  // Analog port for microphone

const int numLeds = _;  // The number of LEDS on the strip
const int dataPin = _;  // The pin the LED strip is connected to

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
  {255, 25, 60}, {255, 42, 9}, {21, 20, 255},
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

  // one of these getMagnitudeX functions must be used with all magnitude related functions
  // getMagnitudeFixed();
  // getMagnitudeAPC();

  // magnitudeBrightness();
  magnitudeLEDsSingle();
}

// SINGLE LED COLOR
void singleLEDColorSetup() {
}

void singleLEDColor() {
}

// ALL LED SAME COLOR
void oneColorSetup() {
}

// Chasing LED
void chasingLEDSetup() {
}

void chasingLED() {
}

void rotate() {
}

// COLOR PALETTE
void colorPaletteSetup() {
}

void colorPaletteRotate() {
}

// MAGNITUDE
void chasingInterruptSetup(unsigned long microseconds) {
}

void getMagnitudeFixed() {
}

void getMagnitudeAPC() {
  getSample();
  agcAvg();
}

void magnitudeBrightness() {
  FastLED.setBrightness(map(magnitude, 0, 255, ___, ___));
  FastLED.show();
  delay(20);
}

void magnitudeLEDsSingle() {
  byte numLEDS = map(magnitude, 0, 255, 0, numLEDs);
  // TODO
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
}

void agcAvg() {                                                   // A simple averaging multiplier to automatically adjust sound sensitivity.
  multAgc = (sampleAvg < 1) ? targetAgc : targetAgc / sampleAvg;  // Make the multiplier so that sampleAvg * multiplier = setpoint
  sampleAgc = sample * multAgc;
  if (sampleAgc > 255) sampleAgc = 255;
  magnitude = sampleAgc;
}