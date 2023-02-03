const int microphonePin     = A4;
const int numberOfReadings  = 128;
int currentReadingIndex     = 0;
int microphoneReadings[numberOfReadings];

void setup() {
  Serial.begin(19200);
  pinMode(microphonePin, INPUT);
}

void loop() {
  readMic();
  Serial.print("Average_over_");
  Serial.print(numberOfReadings);
  Serial.print("_readings:");
  Serial.print(calculateAverage());
  Serial.println("\t0:0\t1023:1023");
}

void readMic() {
  microphoneReadings[currentReadingIndex] = analogRead(microphonePin);
  currentReadingIndex = (currentReadingIndex + 1) % numberOfReadings;
}

double calculateAverage() {
  unsigned long sum = 0;
  for (int i = 0; i < numberOfReadings; i++) {
    sum += microphoneReadings[i];
  }
  return sum / numberOfReadings;
}