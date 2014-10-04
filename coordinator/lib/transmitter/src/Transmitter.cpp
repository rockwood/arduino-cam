#include "XBee.h"
#include "Transmitter.h"

Transmitter::Transmitter(uint32_t shAddress, uint32_t slAddress, uint8_t *payload) {
  XBee _xbee = XBee();
  XBeeAddress64 _address = XBeeAddress64(shAddress, slAddress);
  ZBTxRequest _request = ZBTxRequest(_address, payload, sizeof(payload));
  ZBTxStatusResponse _responseStatus = ZBTxStatusResponse();
}

void Transmitter::setSerial(Stream &serial) {
  _xbee.setSerial(serial);
}

int Transmitter::getStatus() {
  _responseStatus.getDeliveryStatus();
}

uint32_t Transmitter::getShAddress() {
  return _address.getMsb();
}

uint32_t Transmitter::getSlAddress() {
  return _address.getLsb();
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

