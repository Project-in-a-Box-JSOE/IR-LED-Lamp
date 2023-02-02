const int microphonePin   = A4;
const int waveformCenter  = ___; // Use value from previous challenge
const int peakToCenter    = ___; // The largest difference between center and extreme
const int numLEDs         = 6;
int numLEDsOn;

void setup() {
  Serial.begin(38400);
  pinMode(microphonePin, INPUT);
}

void loop() {
  int micIn = analogRead(microphonePin);
  int magnitude = abs(micIn - waveformCenter);

  Serial.print("micIn:");
  Serial.print(micIn);
  Serial.print(",0:");
  Serial.print(0);
  Serial.print(",waveformCenter:");
  Serial.print(waveformCenter);
  Serial.print(",magnitude:");
  Serial.print(magnitude);
  Serial.print(",maxMagnitude:");
  Serial.print(magnitude);
  Serial.print(",1023:");
  Serial.print(1023);

  setNumLEDsOn();
}

void setNumLEDsOn() {
  int numLEDsOn = map(magnitude, 0, peakToCenter, 0, numLEDs);
  numLEDsOn = constrain(mapped, 0, numLEDs);  // Ensure that you stay in range
  Serial.print(",numLEDsOn:");
  Serial.println(numLEDsOn * 100); // Multiply by 100 just so you can see it on the plot
}
