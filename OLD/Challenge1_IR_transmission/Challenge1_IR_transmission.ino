// TimerOne library: https://code.google.com/p/arduino-timerone/downloads/list
#include <Arduino.h>
#include <TimerOne.h>

const int ledPin = 3;
const int sensorPin = 11;

int reading;

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);

    Timer1.initialize(26);
    Timer1.attachInterrupt(callback);
}

void loop() {
    reading = digitalRead(sensorPin);
    Serial.print("The IR sensor is reading:");
    if (reading == 0) {
        Serial.print("IR COMMUNICATION ON");
    }
    else {
        Serial.print("IR COMMUNICATION OFF");
    }
    delay(500);
}

void callback() {
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}