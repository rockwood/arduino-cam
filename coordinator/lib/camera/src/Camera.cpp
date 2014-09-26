#include "XBee.h"
#include "Camera.h"

Camera::Camera(uint32_t sh, uint32_t sl, uint8_t payload[]) {
  XBee _xbee = XBee();
  XBeeAddress64 _addr64 = XBeeAddress64(sh, sl);
  ZBTxRequest _zbTx = ZBTxRequest(_addr64, payload, sizeof(payload));
  ZBTxStatusResponse _txStatus = ZBTxStatusResponse();
}

void Camera::setSerial(Stream &serial) {
  _xbee.setSerial(serial);
}

int Camera::getStatus() {
  _txStatus.getDeliveryStatus();
}

void Camera::sendPayload() {
  _xbee.send(_zbTx);

  if (_xbee.readPacket(500)) {
    // got a response!

    // should be a znet tx status
    if (_xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      _xbee.getResponse().getZBTxStatusResponse(_txStatus);
    }
  } else if (_xbee.getResponse().isError()) {
    // Error reading packet. 
    // nss.println(xbee.getResponse().getErrorCode());
  } else {
    // local XBee did not provide a timely TX Status Response -- should not happen
  }
}

