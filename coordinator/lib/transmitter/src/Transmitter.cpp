#include "XBee.h"
#include "Transmitter.h"

Transmitter::Transmitter(uint32_t shAddress, uint32_t slAddress, uint8_t payload[]): 
  _xbee(XBee()), 
  _address(XBeeAddress64(shAddress, slAddress)), 
  _request(ZBTxRequest(_address, payload, sizeof(payload))), 
  _responseStatus(ZBTxStatusResponse()) {
}

void Transmitter::setSerial(Stream &serial) {
  _xbee.setSerial(serial);
}

int Transmitter::getStatus() {
  _responseStatus.getDeliveryStatus();
}

void Transmitter::sendPayload() {
  _xbee.send(_request);

  if (_xbee.readPacket(500)) {
    // got a response!

    // should be a znet tx status
    if (_xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      _xbee.getResponse().getZBTxStatusResponse(_responseStatus);
    }
  } else if (_xbee.getResponse().isError()) {
    // Error reading packet.
  } else {
    // local XBee did not provide a timely TX Status Response -- should not happen
  }
}

