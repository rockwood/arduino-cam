#include <Joystick.h>
#include <Transmitter.h>

uint8_t payload[] = { 0, 0, 0 };

int statusLed = 13;

Joystick joystick = Joystick(A0, A1, A2);
Transmitter cam1Transmitter = Transmitter(0x0013A200, 0x40AFDCA7, payload);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  cam1Transmitter.setSerial(Serial1);
  pinMode(statusLed, OUTPUT);
}

void loop() {
  joystick.readInto(payload);
  cam1Transmitter.sendPayload();
  delay(100);
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
