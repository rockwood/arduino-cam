#ifndef Camera_h
#define Camera_h

#include "XBee.h"

class Camera {

public:
  Camera(uint32_t sh, uint32_t sl, uint8_t payload[]);
  void setSerial(Stream &serial);  
  void sendPayload();
  int getStatus();
private:
  XBee _xbee;
  XBeeAddress64 _addr64;
  ZBTxStatusResponse _txStatus;
  ZBTxRequest _zbTx;
};

#endif
