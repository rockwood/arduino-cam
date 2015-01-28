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
  int panDistance = translateDistance(payload[0]);
  int tiltDistance = translateDistance(payload[1]);

  writePair(panDistance, _leftPin, _rightPin);
  writePair(tiltDistance, _upPin, _downPin);
}

int Ptz::translateDistance(uint8_t value) {
  int range = 255;
  int threshold = 25;
  int center = range/2;

  int distance = map(value, 0, range, 0 - range, range);

  if (abs(distance) < threshold) {
    distance = 0;
  } 

  return distance;
}

void Ptz::writePair(int distance, int pin1, int pin2) {
  if (distance > 0) {
    analogWrite(pin1, abs(distance));
    analogWrite(pin2, 0);
  }
  else if (distance < 0) {
    analogWrite(pin1, 0);
    analogWrite(pin2, abs(distance));
  }
  else {
    analogWrite(pin1, 0);
    analogWrite(pin2, 0);
  }
}

