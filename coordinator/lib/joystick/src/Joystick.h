#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

class Joystick {
public:
  Joystick(int, int, int);
  void readInto(uint8_t [3]);
private:
  uint8_t readX();
  uint8_t readY();
  uint8_t readZ();
  int _xPin;
  int _yPin;
  int _zPin;
};

#endif
