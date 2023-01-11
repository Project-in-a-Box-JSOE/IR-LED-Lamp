const int redPin    = _;    // pin connected to the red leg of the RGB led
const int greenPin  = _;    // pin connected to the green leg of the RGB led
const int bluePin   = _;    // pin connected to the blue leg of the RGB led

// desired starting LED color (0-255), [0, 0, 0] = black, [255, 255, 255] = white
int red     = 255;
int green   = 0;
int blue    = 0;

const int colorIncrement = 20;  // value the colors will change by

void setup() {
    // Configure all led pins to OUTPUT
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    setColor(red, green, blue); // Set the initial LED color
}

void loop() {
    // Change the led color every time the loop function runs
    red     = ____;
    green   = ____;
    blue    = ____;
    setColor(red, green, blue); // set the LED colors to the new values
}

// This function will change the colors of the connected RGB led to the passed in values
void setColor(int red, int green, int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}

/*
const int redPin    = _;    // pin connected to the red leg of the RGB led
const int greenPin  = _;    // pin connected to the green leg of the RGB led
const int bluePin   = _;    // pin connected to the blue leg of the RGB led

// desired LED color (0-255), [0, 0, 0] = black, [255, 255, 255] = white
int red     = 255;
int green   = 0;
int blue    = 0;

void setup() {
    // set each led pin leg (red, green, blue) to OUTPUT
    pinMode(___);
    pinMode(___);
    pinMode(___);
    setColor(___, ___, ___);    // call on the setColor function to change the led colors
}

void loop() {
    // nothing to do in the loop
}

// This function will change the colors of the connected RGB led to the passed in values
void setColor(int red, int green, int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}
*/