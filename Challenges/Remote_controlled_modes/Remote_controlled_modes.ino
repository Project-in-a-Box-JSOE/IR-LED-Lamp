#include <FastLED.h>
#include <IRremote.h>

// IR remote hex codes
const unsigned long buttonOne       = 0xFFA25D;
const unsigned long buttonTwo       = 0xFF629D;
const unsigned long buttonThree     = 0xFFE21D;
const unsigned long buttonFour      = 0xFF22DD;
const unsigned long buttonFive      = 0xFF02FD;
const unsigned long buttonSix       = 0xFFC23D;
const unsigned long buttonSeven     = 0xFFE01F;
const unsigned long buttonEight     = 0xFFA857;
const unsigned long buttonNine      = 0xFF906F;
const unsigned long buttonAsterisk  = 0xFF6897;
const unsigned long buttonZero      = 0xFF9867;
const unsigned long buttonHashtag   = 0xFFB04F;
const unsigned long buttonUp        = 0xFF18E7;
const unsigned long buttonLeft      = 0xFF10EF;
const unsigned long buttonOk        = 0xFF38C7;
const unsigned long buttonRight     = 0xFF5AA5;
const unsigned long buttonDown      = 0xFF4AB5;
const unsigned long repeat          = -1;
const int decodeType                = 3; // NEC

// FastLED properties
#define CHIPSET     WS2812  // CHIPSET of the LEDs
#define COLOR_CODE  GRB     // color order for the hex code
#define NUM_LEDS    6       // number of LEDs in strip
#define DATA_PIN    3       // port the data pin of LED strip is connected to
CRGB leds[NUM_LEDS];        // array storing the color information for each LED in thestrip

// IR remote properties
const int recvPin = 2;   // Data\ pin the IR receiver is connected to
IRrecv irrecv(recvPin);  // Initialize IR receiver
decode_results results;  // Initialize IR Library

// color things
CRGB initialColor             = (CRGB) CRGB::Purple;
int brightness                = 40;
const int brightnessIncrement = 20; // change in brightness for up/down button presses

int colorIncrement = 1;

void setup() {
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_CODE>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);  // Set the initial brightness to 60/255
  FastLED.show();
  Serial.begin(38400);
  irrecv.enableIRIn();
  pinMode(recvPin, INPUT);
}

enum Mode{nothing, flashingLights, allPurple, rotateLED, singleLED};
Mode curMode = nothing, newMode = nothing;

void loop() {
  // Change modes if the IR receiver sees a protocol matching decodable signal
  if (irrecv.decode(&results)) {
    if (results.decode_type != decodeType) {
      irrecv.resume();  // enable the ir receiver to continue decoding
      return;
    }

    // readRemote reads input from the remote and changes the LED color mode
    // or variables like brightness; returns the new mode
    newMode = readRemote();

    irrecv.resume(); // enable the ir receiver to continue decoding
  }

  // runMode sets the colors of the LEDs based on the current LED color mode
  runMode(newMode != curMode);
  curMode = newMode;
}

int readRemote() {
  Mode newMode = curMode;
  switch (results.value) {
    case buttonOne:
      newMode = flashingLights;
      break;
    case buttonTwo:
      newMode = allPurple;
      break;
    case buttonThree:
      newMode = rotateLED;
      break;
    case buttonFour:
      newMode = singleLED;
      break;
    case buttonFive:
      // Add mode here
      break;
    case buttonSix:
      // Add mode here
      break;
    case buttonSeven:
      // Add mode here
      break;
    case buttonEight:
      // Add mode here
      break;
    case buttonNine:
      // Add mode here
      break;
    case buttonAsterisk:
      turnOff();
      break;
    case buttonZero:
      // Add mode here
      break;
    case buttonHashtag:
      // Add mode here
      break;
    case buttonUp:
      changeBrightness(brightnessIncrement);
      break;
    case buttonLeft:
      // Add mode here
      break;
    case buttonOk:
      // Add mode here
      break;
    case buttonRight:
      // Add mode here
      break;
    case buttonDown:
      changeBrightness(-brightnessIncrement);
      break;
    default:
      break;
  }
  return newMode;
}

// initialize is true if it's the first iteration in this mode
// in other words, when newMode isn't equal to curMode
void runMode(bool initialize){
  
  switch (curMode) {
    case flashingLights:
      cycleColors(initialize);
      break;
    case allPurple:
      setAllColors(CRGB::Purple);
      break;
     case rotateLED:
      rotate(initialize);
      break;
     case singleLED:
      singleLEDColor();
      break;
     default:
      setAllColors((CRGB){0,0,0});
      break;
  }
  
  while (!irrecv.isIdle()){}  // Necessary before each FastLED function call
                              // due to incompatibility of IRremote and FastLED
                              // libraries
  FastLED.show();
}


void cycleColors(bool initialize) {
  if (initialize){
    for (int i=0; i<NUM_LEDS; i++)
      leds[i] = initialColor;
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = (leds[i].r + colorIncrement) % 256;
    leds[i].g = (leds[i].g + colorIncrement) % 256;
    leds[i].b = (leds[i].b + colorIncrement) % 256;
  }
  while (!irrecv.isIdle()){}  // Necessary before each FastLED function call
                              // due to incompatibility of IRremote and FastLED
                              // libraries
  FastLED.show();
}

// Update all leds to the same color
void setAllColors(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setColor(i, color);
  }
}

// Update the colors at the specified index with the new color
void setColor(int index, CRGB color) {
  leds[index] = color;
}

void turnOff() {
  brightness = 0;
  while (!irrecv.isIdle()){}  // Necessary before each FastLED function call
                              // due to incompatibility of IRremote and FastLED
                              // libraries
  FastLED.setBrightness(brightness);
  while (!irrecv.isIdle()){}  // Necessary before each FastLED function call
                              // due to incompatibility of IRremote and FastLED
                              // libraries
  FastLED.show();
}

void changeBrightness(int brightnessChange) {
  brightness = constrain(brightness + brightnessChange, 0, 255);
  while (!irrecv.isIdle()){}  // Necessary before each FastLED function call
                              // due to incompatibility of IRremote and FastLED
                              // libraries
  FastLED.setBrightness(brightness);
  while (!irrecv.isIdle()){}  // Necessary before each FastLED function call
                              // due to incompatibility of IRremote and FastLED
                              // libraries
  FastLED.show();
}

void rotate(bool initialize) {
  if (initialize){
    CRGB palette[NUM_LEDS] = {
      {255, 25, 60}, {255, 42, 9}, {21, 20, 255},
      {10, 255, 0}, {60, 35, 255}, {0, 0, 0}
    };
    for (int i=0; i<NUM_LEDS; i++){
      leds[i] = palette[i];
    }
  }
  
  CRGB first = leds[0];
  for (int i=0; i+1<NUM_LEDS; i++){
    leds[i] = leds[i+1];
  }
  leds[NUM_LEDS-1] = first;
}

void singleLEDColor() {
  // TODO: cycle through colors of the first LED
  leds[0].r = (leds[0].r + 1) % 256;
  leds[0].g = (leds[0].g + 1) % 256;
  leds[0].b = (leds[0].b + 1) % 256;
}