const int microphonePin   = A4;
const int ledPin          = 13;
const int waveformCenter  = __;
const int clapThreshold   = __; // Clap a few times to see what magnitude you get
int maxMagnitude          = 0;

void setup() {
  Serial.begin(9600);
  pinMode(microphonePin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int micIn = analogRead(microphonePin);
  int magnitude = abs(micIn - waveformCenter);
  Serial.print("micIn:")
  Serial.print(micIn);
  Serial.print(",0:");
  Serial.print(0);
  Serial.print(",maxMagnitude:");
  Serial.print(maxMagnitude + waveformCenter);
  Serial.print(",minMagnitude:");
  Serial.print(waveformCenter - maxMagnitude);
  Serial.print(",1023:");
  Serial.println(1023);
  delay(50);

  if (maxMagnitude < magnitude) {
    maxMagnitude = magnitude;
  }
  /*if (magnitude > clapThreshold) {
    Serial.println("Loud noise detected!!");
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }*/
}
