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

// FastLED properties
#define CHIPSET     WS2812  // CHIPSET of the LEDs
#define COLOR_CODE  RGB     // color order for the hex code
#define NUM_LEDS    6       // number of LEDs in strip
#define DATA_PIN    3       // port the data pin of LED strip is connected to
CRGB leds[NUM_LEDS];        // array storing the color information for each LED in thestrip

// IR remote properties
const int recvPin = 2;   // Data pin the IR receiver is connected to
IRrecv irrecv(recvPin);  // Initialize IR receiver
decode_results results;  // Initialize IR Library

// color things
CRGB initialColor             = (CRGB) CRGB::Purple;
byte brightness               = 40;
const int brightnessIncrement = 20;

void setup() {
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_CODE>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);  // Set the initial brightness to 60/255
  Serial.begin(9600);
}

void loop() {
  remoteButtonPress();
}

bool remoteButtonPress() {
  bool returnValue = true;

  if (irrecv.decode(&results)) {
    switch (results.value) {
      case buttonOne:
        cycleColors();
        break;
      case buttonTwo:
        // Add mode here
        break;
      case buttonThree:
        // Add mode here
        break;
      case buttonFour:
        // Add mode here
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
        returnValue = false;
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
        returnValue = false;
        break;
      default:
        Serial.print("UNKNOWN CODE: ");
        Serial.println(results.value);
        returnValue = false;
        break;
    }
  }
  return returnValue;
}

void cycleColors() {
  int red                 = initialColor.r;
  int green               = initialColor.g;
  int blue                = initialColor.b;
  int brightnessIncrement = 25;

  while (true) {
    red   = (red + brightnessIncrement) % 256;
    green = (green + brightnessIncrement) % 256;
    blue  = (blue + brightnessIncrement) % 256;

    setAllColors(red, green, blue);

    FastLED.show();       // Send changes to the LED strip
    remoteButtonPress();  // Change modes on remote button press
  }
}

// Update all leds to the same color
void setAllColors(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setColor(i, red, green, blue);
  }
}

// Update the colors at the specified index with the new color
void setColor(int index, byte red, byte green, byte blue) {
  leds[index] = (CRGB){.r = red, .g = green, .b = blue};
}

void turnOff() {
  FastLED.setBrightness(0);
  FastLED.show();
}

void changeBrightness(int brightnessChange) {
  brightness = constrain(brightness + brightnessChange, 0, 255);
  FastLED.setBrightness(brightness);
  FastLED.show();
}
