#include <Joystick.h>
#include <Camera.h>

uint8_t payload[] = { 0, 0, 0 };

int statusLed = 13;

Joystick joystick = Joystick(A0, A1, A2);
Camera cam1 = Camera(0x13A200, 0x40AFDCA7, payload);

void setup() {
  Serial.begin(9600);
  cam1.setSerial(Serial);
  pinMode(statusLed, OUTPUT);
}

void loop() {
  joystick.readInto(payload);
  cam1.sendPayload();
  flashLed(statusLed, 3, payload[0]);
  delay(1000);  
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
