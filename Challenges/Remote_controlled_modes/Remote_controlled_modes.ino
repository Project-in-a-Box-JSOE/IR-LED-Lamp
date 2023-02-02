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
const int brightnessIncrement = 20;

void setup() {
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_CODE>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);  // Set the initial brightness to 60/255
  FastLED.show();
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(recvPin, INPUT);
}

void loop() {
  
  if (irrecv.decode(&results)) {
    if (results.decode_type != decodeType) {
      irrecv.resume();
      return;
    }
    switch (results.value) {
      case buttonOne:
        cycleColors(buttonOne);
        break;
      case buttonTwo:
        // Add mode here
        setAllColors(CRGB::Purple);
        while (!irrecv.isIdle()){}
        FastLED.show();
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
    irrecv.resume();
  }
//  remoteButtonPress();
}

bool remoteButtonPress(unsigned long currentCase) {
  bool returnValue = false;
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.decode_type == decodeType) {
      returnValue = true;
      if (results.value == buttonUp) {
        changeBrightness(brightnessIncrement);
        returnValue = false;
      }
      else if (results.value == buttonDown) {
        changeBrightness(-brightnessIncrement);
        returnValue = false;
      }
      else if (results.value == repeat || results.value == currentCase) {
        returnValue = false;
      }
    }
    
    irrecv.resume();
  }
  return returnValue;
}

void cycleColors(unsigned long theCase) {
  int red                 = initialColor.r;
  int green               = initialColor.g;
  int blue                = initialColor.b;
  int colorIncrement      = 1;

  while (true) {
    red   = (red + colorIncrement) % 256;
    green = (green + colorIncrement) % 256;
    blue  = (blue + colorIncrement) % 256;

    setAllColors((CRGB) {red, green, blue});

    while (!irrecv.isIdle()){}
    FastLED.show(); // Send changes to the LED strip
    if(remoteButtonPress(theCase)) return;  // Change modes on remote button press
  }
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
  while (!irrecv.isIdle()){}
  FastLED.setBrightness(brightness);
  while (!irrecv.isIdle()){}
  FastLED.show();
}

void changeBrightness(int brightnessChange) {
  brightness = constrain(brightness + brightnessChange, 0, 255);
  while (!irrecv.isIdle()){}
  FastLED.setBrightness(brightness);
  while (!irrecv.isIdle()){}  
  FastLED.show();
}
