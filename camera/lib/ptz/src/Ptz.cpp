#include "Arduino.h"
#include "Ptz.h"

Ptz::Ptz(int upPin, int downPin, int leftPin, int rightPin): 
  _upPin(upPin),
  _downPin(downPin),
  _leftPin(leftPin),
  _rightPin(rightPin) 
{
  pinMode(_upPin, OUTPUT);
  pinMode(_downPin, OUTPUT);
  pinMode(_leftPin, OUTPUT);
  pinMode(_rightPin, OUTPUT);
}

void Ptz::writePayload(uint8_t *payload) {
  if (payload[0] > 128) {
    digitalWrite(_upPin, LOW);
  } else {
    digitalWrite(_downPin, LOW);
  }
}

