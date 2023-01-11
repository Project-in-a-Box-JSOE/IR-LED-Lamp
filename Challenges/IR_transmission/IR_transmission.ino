// TimerOne library: https://code.google.com/p/arduino-timerone/downloads/list
// Inspiried by UCSD ECE 5 Lab 1
#include <TimerOne.h>

const int ledPin = 3;       // The IR led pin (must be interrupt pin)
const int sensorPin = __;   // The pin the data leg of the IR receiver is connected to

int reading;                // Variable to store IR reading value

void setup() {
    Serial.begin(9600);                 // Start up the Serial port with 9600 baud
    pinMode(sensorPin, ______);         // Configure the IR receiver as an INPUT
    pinMode(ledPin, ______);            // Configure the IR led as an OUTPUT

    Timer1.initialize(26);              // start time to run every 26 microseconds 1/26us = 38kHz
    Timer1.attachInterrupt(callback);   // connect the callback function to run every interrupt
}

void loop() {
    if (digitalRead(sensorPin) == 0) {  // If the sensor reads 0, IR signals are being received
        Serial.println("IR COMMUNICATION ON");
    }
    else {
        Serial.println("IR COMMUNICATION OFF");
    }
    delay(500); // Delay to slow serial monitor output
}

// This function will run every 26 microseconds
void callback() {
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);  // Toggle the IR LED (bitwise XOR)
}