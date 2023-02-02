const int microphonePin   = A4;
const int ledPin          = 13;
const int waveformCenter  = ___;  // use value from the previous challenge
const int clapThreshold   = 1023; // Clap a few times to see what magnitude you get

void setup() {
  Serial.begin(38400);
  pinMode(microphonePin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
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
  Serial.print(",clapThreshold:");
  Serial.print(clapThreshold);
  Serial.print(",1023:");
  Serial.println(1023);
  delay(50);

  if (magnitude > clapThreshold) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
  }
}
