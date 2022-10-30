#include <IRremote.h>
#include <FastLED.h>

#define ON_OFF_KEY 0xFF629D
#define RIGHT_KEY 0xFF7A85
#define LEFT_KEY 0xFF30CF
#define UP_KEY 0xFF9867
#define DOWN_KEY 0xFF38C7
#define CIRCLE_KEY 0xFF18E7
#define A_KEY 0xFF22DD
#define B_KEY 0xFF02FD
#define C_KEY 0xFFC23D
#define KEY_REPEAT 0xFFFFFFFF

#define NUM_LEDS 6
#define DATA_PIN 3
#define COLOR_CODE RGB
#define CHIPSET WS2812
#define RECV_PIN 2
#define UPDATES_PER_SECOND 20

#define STATUS_PIN 13

IRrecv irrecv(RECV_PIN);
decode_results results;   // Initialize IR Library
CRGB leds[NUM_LEDS];
float glowIncr[NUM_LEDS];
float colorChg[3];
byte color[3] = {255, 0, 0};
byte old_color[3] = {156, 86, 191};
int colorStep = 500;
bool inc = false;
bool changed = true;
bool first = true;
byte BRIGHTNESS = 70;
int loadThreshold = 500;
bool waitForLoad = false;
byte presetHeld = 0;
bool rgbMode = false;
byte rgb = 0;

byte mode = 1; // 00000abc, c - on/off
/*
 * a  b mode
 * 0  0 light
 * 0  1 glow
 * 1  0 glow seq
 * 1  1 rotate color
 */

unsigned long startSigTimer;
unsigned long prevSigPress;
unsigned long prevSig;
unsigned long currSig;
int threshold = 5000;

const TProgmemRGBPalette16 thomaColors_p FL_PROGMEM = {
  0xefc56f, 0x4a3934, 0x881d2d, 0xc9a55b, 0x27404d,
  0xefc56f, 0x4a3934, 0x881d2d, 0xc9a55b, 0x27404d,
  0xefc56f, 0x4a3934, 0x881d2d, 0xc9a55b, 0x27404d,
  0x66585e
};

struct PRESET {
  byte color[3];
  byte mode;
  byte brightness;
};

PRESET presets[3];

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(STATUS_PIN, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  startSigTimer = millis();
  prevSigPress - startSigTimer;
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_CODE>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  for(int i = 0; i < NUM_LEDS; i++) {
    glowIncr[i] = colorStep/4;
  }
  presets[0].color[0] = 255;
  presets[0].color[1] = 0;
  presets[0].color[2] = 0;
  presets[0].mode = 1;
  presets[0].brightness = 70;

  presets[1].color[0] = 156;
  presets[1].color[1] = 86;
  presets[1].color[2] = 191;
  presets[1].mode = 3;
  presets[1].brightness = 70;
  
  presets[2].color[0] = 156;
  presets[2].color[1] = 86;
  presets[2].color[2] = 191;
  presets[2].mode = 7;
  presets[2].brightness = 70;
  /*PRESET B = {{255, 0, 0}, 3, 50}; // Glow red       011
  PRESET C = {{255, 0, 0}, 5, 50}; // Rotate red     101
  presets[0] = &A;
  presets[1] = &B;
  presets[2] = &C;*/
}

void loop() {
  //if((prevSig == A_KEY || prevSig == B_KEY || prevSig == C_KEY) && (millis() - prevSigPress) > loadThreshold && (millis() - startSigTimer) 
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    if (results.value != KEY_REPEAT) {
      currSig = results.value;
      switch (currSig) {
        case ON_OFF_KEY:
          if(mode & 1) {  // currently on
            old_color[0] = color[0];
            old_color[1] = color[1];
            old_color[2] = color[2];
            color[0] = 0;
            color[1] = 0;
            color[2] = 0; 
            //Serial.println("Turning off");
          }
          else {          // currently off
            color[0] = old_color[0];
            color[1] = old_color[1];
            color[2] = old_color[2];
            //Serial.println("Turning on");
          }
          light();
          mode = mode ^ 1; // mode bitwise xor with 001
          prevSig = ON_OFF_KEY;
          buttPressLed();
          //waitForLoad = false;
          break;
        case LEFT_KEY:
          // ADD RGB EDIT MODE
          if(rgbMode) {
            rgb = (rgb - 1) % 3;
            prevSig = LEFT_KEY;
            buttPress();
            buttPressLed();
          }
          else {
            mode = ((mode & 1) + ((mode & 6) - 2)) & 7;
            changed = true;
            prevSig = LEFT_KEY;
            buttPressLed();
          }
          //waitForLoad = false;
          break;
        case RIGHT_KEY:
          // ADD RGB EDIT MODE
          if(rgbMode) {
            rgb  = (rgb + 1) % 3;
            prevSig = RIGHT_KEY;
            buttPress();
            buttPressLed();
          }
          else {
            mode = ((mode & 1) + ((mode & 6) + 2)) & 7;
            changed = true;
            prevSig = RIGHT_KEY;
            buttPressLed();
          }
          //waitForLoad = false;
          break;
        case UP_KEY:
          // ADD RGB EDIT MODE
          if(rgbMode) {
            color[rgb] = constrain(color[rgb] + 3, 0, 255);
            prevSig = UP_KEY;
            buttPressLed();
          }
          else {
            BRIGHTNESS = constrain(BRIGHTNESS + 10, 0, 255);
            FastLED.setBrightness(BRIGHTNESS);
            prevSig = UP_KEY;
            buttPressLed();
          }
          //waitForLoad = false;
          break;
        case DOWN_KEY:
          // ADD RGB EDIT MODE
          if(rgbMode) {
            color[rgb] = constrain(color[rgb] - 3, 0, 255);
            prevSig = DOWN_KEY;
            buttPressLed();
          }
          else {
            BRIGHTNESS = constrain(BRIGHTNESS - 10, 0, 255);
            FastLED.setBrightness(BRIGHTNESS);
            prevSig = DOWN_KEY;
            buttPressLed();
          }
          //waitForLoad = false;
          break;
        case CIRCLE_KEY:
          // TODO
          rgbMode = !rgbMode;
          rgb = 0;
          prevSig = CIRCLE_KEY;
          //waitForLoad = false;
          buttPress();
          buttPressLed();
          break;
        case A_KEY:
          /*startSigTimer = millis();
          presetHeld = 0;
          prevSig = A_KEY;*/
          buttPressLed();
          loadPreset(0);
          break;
        case B_KEY:
          /*startSigTimer = millis();
          presetHeld = 1;
          prevSig = B_KEY;*/
          buttPressLed();
          loadPreset(1);
          break;
        case C_KEY:
          /*startSigTimer = millis();
          presetHeld = 2;
          prevSig = C_KEY;*/
          buttPressLed();
          loadPreset(2);
          break;
      }
    }
    else { // REPEAT
      if(rgbMode) {
        switch(prevSig) {
          case UP_KEY:
            color[rgb] = constrain(color[rgb] + 3, 0, 255);
            buttPressLed();
            break;
          case DOWN_KEY:
            color[rgb] = constrain(color[rgb] - 3, 0, 255);
            buttPressLed();
            break;
        }
      }
      else {
        switch(prevSig) {
          case UP_KEY:
            BRIGHTNESS = constrain(BRIGHTNESS + 4, 0, 255);
            FastLED.setBrightness(BRIGHTNESS);
            buttPressLed();
            break;
          case DOWN_KEY:
            BRIGHTNESS = constrain(BRIGHTNESS - 4, 0, 255);
            FastLED.setBrightness(BRIGHTNESS);
            buttPressLed();
            break;
        }
        
      }
      /*if((millis() - startSigTimer) > threshold) {
        Serial.print("Setting preset...PRESET");Serial.println(presetHeld);
        startSigTimer = millis();
        // Save preset
        savePreset(presetHeld);
        // Do something to show preset saved
        FastLED.setBrightness(0);
        color[0] = 156;
        color[1] = 86;
        color[2] = 191;
        delay(15);
        FastLED.setBrightness(10);
        FastLED.show();
        delay(20);
        FastLED.setBrightness(0);
        FastLED.show();
        delay(15);
        loadPreset(presetHeld);
        FastLED.show();
      }*/
    }
    //prevSigPress = millis();
    irrecv.resume();
  }

  //glow(DEFAULT_COLOR_STEP*2);
  //glowSeq(DEFAULT_COLOR_STEP);
  //light();
  //changed = first?true:false;
  //first = false;
  //FastLED.show();
  if(mode&1) {
    switch(mode & 6) { // bitwise and with 110
      case 2:
        // mode = 01x - glow
        glow();
        break;
      case 4:
        // mode = 10x - glow & rotate(seq)
        glowSeq();
        break;
      case 6:
        // mode = 11x - rotate color
        static uint8_t startIndex;
        startIndex = startIndex + 1;
        colorSeq(startIndex);
        break;
      case 0:
        // mode = 00x - just light up
        light();
        break;
    }
  }
  else {  // currently on
    old_color[0] = color[0];
    old_color[1] = color[1];
    old_color[2] = color[2];
    color[0] = 0;
    color[1] = 0;
    color[2] = 0; 
    light(); 
  }
  FastLED.show();
}

void buttPress() {
  FastLED.setBrightness(0);
  FastLED.show();
  delay(30);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
}

void buttPressLed() {
  digitalWrite(13, LOW);
  delay(5);
  digitalWrite(STATUS_PIN, HIGH);
  delay(10);
  digitalWrite(13, LOW);
}

void light() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = color[0];
    leds[i].g = color[1];
    leds[i].b = color[2];
  }
}

void glow() {
  int r = color[0];
  int g = color[1];
  int b = color[2];
  if(changed) {
    colorChg[0] = (r+0.0)/colorStep;
    colorChg[1] = (g+0.0)/colorStep;
    colorChg[2] = (b+0.0)/colorStep;
    changed = false;
  }
  else {
    if(glowIncr[0] > colorStep) {
      glowIncr[0] = -colorStep;
    }
    else if (glowIncr[0] > (-colorStep / 6) && glowIncr[0] < 0) {
      glowIncr[0] = colorStep / 6;
    }
    else {
      glowIncr[0]++;
    }
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i].r = colorChg[0]*abs(glowIncr[0]);
      leds[i].g = colorChg[1]*abs(glowIncr[0]);
      leds[i].b = colorChg[2]*abs(glowIncr[0]);
    }
  }
}

void glowSeq() {
  int r = color[0];
  int g = color[1];
  int b = color[2];
  if(changed) {
    colorChg[0] = (r+0.0)/colorStep;
    colorChg[1] = (g+0.0)/colorStep;
    colorChg[2] = (b+0.0)/colorStep;

    for(int i = 0; i < NUM_LEDS; i++) {
       glowIncr[i] = i*(colorStep/NUM_LEDS);
    }
    changed = false;
  }
  else {
    for(int i = 0; i < NUM_LEDS; i++) {
      if(glowIncr[i] > colorStep) {
        glowIncr[i] = -colorStep;
      }
      else if (glowIncr[i] > (-colorStep / 8) && glowIncr[i] < 0) {
        glowIncr[i] = colorStep / 8;
      }
      else {
        glowIncr[i]++;
      }
      leds[i].r = colorChg[0]*abs(glowIncr[i]);
      leds[i].g = colorChg[1]*abs(glowIncr[i]);
      leds[i].b = colorChg[2]*abs(glowIncr[i]);
    }
  }
}

void colorSeq(uint8_t colorIndex) {
  if(changed) {
    changed = false;
  }
  else {
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(thomaColors_p, colorIndex, 255, LINEARBLEND);
        //leds[i] = ColorFromPalette(RainbowColors_p, colorIndex, 255, LINEARBLEND);
        colorIndex += 3;
    }
  }
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void savePreset(byte presetInd) {
  PRESET* tmp = &(presets[presetInd]);
  tmp->color[0] = color[0];
  tmp->color[1] = color[1];
  tmp->color[2] = color[2];
  
  tmp->brightness = BRIGHTNESS;

  tmp->mode = mode;
}

void loadPreset(byte presetInd) {
  PRESET temp = presets[presetInd];
  color[0] = temp.color[0];
  color[1] = temp.color[1];
  color[2] = temp.color[2];

  BRIGHTNESS = temp.brightness;
  FastLED.setBrightness(BRIGHTNESS);

  mode = temp.mode;
}
