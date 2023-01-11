const int ledPin = _;           // the pin number the led is connected to

void setup() {
    pinMode(ledPin, ______);    // Configure the ledPin as an OUTPUT
}

void loop() {
    digitalWrite(______, ____); // turn the led on (HIGH)
    delay(1000);                // pause the code the a 1000 ms
    digitalWrite(ledPin, LOW);  // turn the led off (LOW)
    delay(____);                // pause the code for a second (1000 ms)
}