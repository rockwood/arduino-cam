#include "Arduino.h"
#include "Lanc.h"

const int REPEAT_COUNT = 5;
const int BIT_DURATION = 104;

Lanc::Lanc(int readPin, int writePin) {
  pinMode(readPin, OUTPUT);
  pinMode(writePin, OUTPUT);
  _readPin = readPin;
  _writePin = writePin;
}

void Lanc::writePair(byte command1, byte command2) {
  for (int i = 0; i < REPEAT_COUNT; i++) {  //repeat to make sure the camera accepts the command
    while (pulseIn(_readPin, HIGH) < 5000) { }
    
    delayMicroseconds(BIT_DURATION);  //wait START bit duration
    
    writeByte(command1);
    
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(_writePin, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1
    
    while (digitalRead(_readPin)) { }
    
    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(BIT_DURATION);  //wait START bit duration
    
    writeByte(command2);
    
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(_writePin, LOW);
  }
}

void Lanc::writeByte(byte command) {
  for (byte bitmask = 1; bitmask > 0; bitmask <<= 1) {
    if (command & bitmask){
      digitalWrite(_writePin, HIGH);
    }
    else{
      digitalWrite(_writePin, LOW);
    }
    delayMicroseconds(BIT_DURATION);
  }
}
