#include <IRremote.h>
#include <FastLED.h>

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
CRGB leds[NUM_LEDS];        // array storing the color information for each LED in the strip

// IR remote properties
const int recvPin = 2;  // Data pin the IR receiver is connected to
IRrecv irrecv(recvPin); // Initialize IR receiver
decode_results results; // Initialize IR Library

// color things
const int initialColor  = CRGB::Purple;
byte brightness         = 20;
byte currentMode        = 0;
byte numModes;  // Will be given a value in setup()

// This struct represents each mode
// with a setup function and the main function that would be called on loop
struct mode {
  void (*modeSetup)();
  void (*modeFunction)();
};

// Declare functions here so that you can call on them before they are defined
void clearStrip();
void rotate();
void singleLEDSetup();
void chasingLEDSetup();
void colorPaletteSetup();
void breathe();

mode modes[] = {
  {.modeSetup=chasingLEDSetup, .modeFunction=rotate},
  {colorPaletteSetup, breathe}
};

void (*currentFunction) () = rotate;

void setup() {
  Serial.begin(9600);                       // Initialize the Serial port
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_CODE>(leds, NUM_LEDS); // Set up FastLED
  irrecv.enableIRIn();                      // Start the receiver
  numModes = sizeof(modes) / sizeof(mode);  // Find the number of modes
  delay(200);                               // Add delay to make sure things are setup
}

void loop() {
  if (irrecv.decode(&results)) {
    clearStrip(); // Just clear the strip before making changes to avoid confusing behavior
    switch (results.value) {
      case buttonOne:
        // Breathing lights using the color palette setup
        colorPaletteSetup();
        currentFunction = breathe;
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
        // Add mode here (maybe control power?)
        break;
      case buttonZero:
        // Add mode here
        break;
      case buttonHashtag:
        // Add mode here
        break;
      case buttonUp:
        // Add mode here (maybe control brightness?)
        break;
      case buttonLeft:
        currentMode = (currentMode == 0) ? numModes - 1 : currentMode - 1;
        modes[currentMode].modeSetup();
        currentFunction = modes[currentMode].modeFunction;
        break;
      case buttonOk:
        // Add mode here
        break;
      case buttonRight:
        currentMode = (currentMode + 1) % numModes;
        modes[currentMode].modeSetup();
        currentFunction = modes[currentMode].modeFunction;
        break;
      case buttonDown:
        // Add mode here (maybe control brightness?)
        break;
    }

    irrecv.resume();  // Re-enable the IR receiver
  }

  currentFunction();  // Call on the current mode function
}

void clearStrip() {
  // Reset color and brightness of the LED strip
  brightness = 42;
  FastLED.setBrightness(brightness);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[0] = CRGB::Black;
  }
  FastLED.show();
}

void rotate() {
  // Copy your rotate code here
  Serial.println("rotate");
}

void singleLEDSetup() {
  // Copy your singleLEDSetup code here
  Serial.println("single LED setup");
}

void chasingLEDSetup() {
  // Copy your chasingLEDSetup code here
  Serial.println("chasingLEDSetup");
}

void colorPaletteSetup() {
  // Copy your colorPaletteSetup code here
  Serial.println("colorPaletteSetup");
}

void breathe() {
  Serial.println("breathe");
}
