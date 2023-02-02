#include <IRremote.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(RECV_PIN, INPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Hex code: ");
    Serial.print(results.value, HEX);
    if (results.value == -1) {
      Serial.print(" REPEAT (ignore)");
    }
    Serial.println();
    irrecv.resume(); // resume receiver
  }
}