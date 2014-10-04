#include "XBee.h"
#include "receiver.h"

Receiver::Receiver() {
  XBee _xbee = XBee();
  XBeeResponse _response = XBeeResponse();
  ZBRxResponse _rx = ZBRxResponse();
  ModemStatusResponse _msr = ModemStatusResponse();
}

void Receiver::beginSerial(Stream &serial) {
  _xbee.begin(serial);
}

void Receiver::receivePayload(uint8_t payload[]) { 
  _xbee.readPacket();

  if (_xbee.getResponse().isAvailable()) {
    // got something

    if (_xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      // got a zb rx packet

      // now fill our zb rx class
      _xbee.getResponse().getZBRxResponse(_rx);

      if (_rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
        // the sender got an ACK
      } else {
        // we got it (obviously) but sender didn't get an ACK
      }
      payload[0] = _rx.getData(0);
      payload[1] = _rx.getData(1);
      payload[2] = _rx.getData(2);
    } else if (_xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) {
      _xbee.getResponse().getModemStatusResponse(_msr);
      // the local XBee sends this response on certain events, like association/dissociation

      if (_msr.getStatus() == ASSOCIATED) {
        // yay this is great.
      } else if (_msr.getStatus() == DISASSOCIATED) {
        // this is awful.. flash led to show our discontent
      } else {
        // another status
      }
    } else {
      // not something we were expecting
    }
  } else if (_xbee.getResponse().isError()) {
  }
}

