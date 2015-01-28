#include "Arduino.h"
#include "Joystick.h"

Joystick::Joystick(int xPin, int yPin, int zPin) {
  _xPin = xPin;
  _yPin = yPin;
  _zPin = zPin;
  pinMode(_xPin, INPUT);
  pinMode(_yPin, INPUT);
  pinMode(_zPin, INPUT);
}

uint8_t Joystick::readPin(int pin) {
  return analogRead(pin) / 4;
}

void Joystick::readInto(uint8_t arr[3]) {
  arr[0] = readPin(_xPin);
  arr[1] = readPin(_yPin);
  arr[2] = readPin(_zPin);
}
