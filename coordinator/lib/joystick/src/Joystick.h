#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

class Joystick {

public:
  Joystick(int, int, int);
  void readInto(uint8_t [3]);

private:
  uint8_t readPin(int);
  int _xPin;
  int _yPin;
  int _zPin;
};

#endif
