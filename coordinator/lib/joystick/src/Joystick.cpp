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

uint8_t Joystick::readX() {
  return analogRead(_xPin) / 4;
}

uint8_t Joystick::readY() {
  return analogRead(_yPin) / 4;
}

uint8_t Joystick::readZ() {
  return analogRead(_zPin) / 4;
}

void Joystick::readInto(uint8_t arr[3]) {
  arr[0] = readX();
  arr[1] = readY();
  arr[2] = readZ();
}
