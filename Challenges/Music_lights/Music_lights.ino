const int microphonePin   = A4;
const int ledPin          = 13;
const int waveformCenter  = __;
const int peakToCenter    = __; // The largest difference between center and extreme
const int numLEDs         = 6;

void setup() {
  Serial.begin(9600);
  pinMode(microphonePin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int micIn = analogRead(microphonePin);
  int magnitude = abs(micIn - waveformCenter);

  /*
  Serial.print("micIn:")
  Serial.print(micIn);
  Serial.print(",0:");
  Serial.print(0);
  Serial.print(",1023:");
  Serial.println(1023);
  */

  int mapped = map(magnitude, 0, peakToCenter, numLEDs);
  Serial.print("numLEDsOn:")
  Serial.println(mapped);
}
