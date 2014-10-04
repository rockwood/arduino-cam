#ifndef Transmitter_h
#define Transmitter_h

#include "XBee.h"

class Transmitter {
  public:
    Transmitter(uint32_t shAddress, uint32_t slAddress, uint8_t *payload);
    void setSerial(Stream &serial);  
    void sendPayload();
    int getStatus();
    uint32_t getShAddress();
    uint32_t getSlAddress();
  private:
    XBee _xbee;
    XBeeAddress64 _address;
    ZBTxRequest _request;
    ZBTxStatusResponse _responseStatus;
};

#endif
