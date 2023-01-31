const int microphonePin     = A4;
const int numberOfReadings  = 3200;
int currentReadingIndex     = 0;
int microphoneReadings[numberOfReadings];

void setup() {
  Serial.begin(9600);
  pinMode(microphonePin);
}

void loop() {
  readMic();
  Serial.print("Average over ");
  Serial.print(numberOfReadings);
  Serial.print(" readings: ");
  Serial.println(calculateAverage);
}

void readMic() {
  for (int i = 0; i < numberOfReadings; i++) {
    microphoneReadings[i] = analogRead(microphonePin);
  }
}

double calculateAverage() {
  unsigned int sum = 0;
  for (int i = 0; i < numberOfReadings; i++) {
    sum += microphoneReadings[i];
  }
  return sum / numberOfReadings;
}
