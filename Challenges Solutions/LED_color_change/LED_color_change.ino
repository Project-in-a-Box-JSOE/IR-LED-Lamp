const int redPin = 5;
const int greenPin = 6;
const int bluePin = 9;

int red = 0;
int green = 21;
int blue = 42;

const int colorIncrement = 20;

void setup() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    setColor(red, green, blue);
}

void loop() {
    red = (red + colorIncrement) % 255;
    green = (green + colorIncrement) % 255;
    blue = (blue + colorIncrement) % 255;
    setColor(red, green, blue);
}

void setColor(int red, int green, int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}

/*
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 9;

int red = 0;
int green = 21;
int blue = 42;

void setup() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    setColor(red, green, blue);
}

void loop() {
    
}

void setColor(int red, int green, int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}
*/