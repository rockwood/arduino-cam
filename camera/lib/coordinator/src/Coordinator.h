#ifndef coordinator_h
#define coordinator_h

#include "XBee.h"

class Coordinator {

public:
  Coordinator();
  void receivePayload(uint8_t payload[]);
  void beginSerial(Stream &serial);
private:
  XBee _xbee;
  XBeeResponse _response;
  ZBRxResponse _rx;
  ModemStatusResponse _msr;
};

#endif
