#include <Coordinator.h>

uint8_t payload[] = { 0, 0, 0 };

Coordinator coordinator = Coordinator();

int successLed = 3;
int errorLed = 5;

void setup() {
  Serial.begin(9600);
  coordinator.beginSerial(Serial);
  pinMode(successLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
}

void loop() {
  coordinator.receivePayload(payload);
  flashLed(successLed, 3, payload[0]);
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
