#ifndef ptz_h
#define ptz_h

#include "Arduino.h"

class Ptz {

public:
  Ptz(int, int, int, int);
  void writePayload(uint8_t [3]);
private:
  int _upPin;
  int _downPin;
  int _leftPin;
  int _rightPin;
};

#endif
