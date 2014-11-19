#ifndef receiver_h
#define receiver_h

#include "XBee.h"

class Receiver {

public:
  Receiver();
  void receivePayload(uint8_t payload[]);
  void beginSerial(Stream &serial);
  int getStatus();
private:
  XBee _xbee;
  XBeeResponse _response;
  ZBRxResponse _rx;
  ModemStatusResponse _msr;
};

#endif
