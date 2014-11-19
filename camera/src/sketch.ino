#include <Receiver.h>

uint8_t payload[] = { 0, 0, 0 };

Receiver receiver = Receiver();

int successLed = 3;
int errorLed = 5;

void setup() {
  Serial.begin(9600);
  receiver.beginSerial(Serial1);
  pinMode(successLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
}

void loop() {
  receiver.receivePayload(payload);
  printPayload();
  delay(80); // Must be faster than the coordinator
}

void flashLed(int pin, int times, int wait) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(wait);
    digitalWrite(pin, LOW);

    if (i + 1 < times) {
      delay(wait);
    }
  }
}

void printPayload() {
  Serial.print(" X: ");
  Serial.print(payload[0]);
  Serial.print(" Y: ");
  Serial.print(payload[1]);
  Serial.println();
}
