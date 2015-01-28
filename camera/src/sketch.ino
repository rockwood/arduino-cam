#include <Receiver.h>
#include <Ptz.h>

uint8_t payload[] = { 0, 0, 0 };

Receiver receiver = Receiver();
Ptz ptz = Ptz(6, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  receiver.beginSerial(Serial1);
}

void loop() {
  receiver.receivePayload(payload);
  ptz.writePayload(payload);
  debug();
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

void debug() {
  Serial.print(" X: ");
  Serial.print(payload[0]);
  Serial.print(" Y: ");
  Serial.print(payload[1]);
  Serial.println();
}
