const int micPin = A4;
    
void setup() {
  Serial.begin(9600);
  pinMode(micPin, INPUT);
}

void loop() {
  int micIn = analogRead(micPin);
  Serial.print("mic:");
  Serial.print(micIn);
  // Maintain the range of the plot at 0-1023
  Serial.print("\t0:");
  Serial.print(0);
  Serial.print("\t1023:");
  Serial.println(1023);
}
