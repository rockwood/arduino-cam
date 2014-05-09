/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Lanc_h
#define Lanc_h

#include "Arduino.h"

class Lanc {
  public:
    Lanc(int writePin, int readPin);
    void writePair(byte command1, byte command2);
  private:
    void writeByte(byte command);
    int _writePin;
    int _readPin;
};

#endif
