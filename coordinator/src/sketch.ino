#include <Joystick.h>
// #include <Transmiter.h>

uint8_t payload[] = { 0, 0, 0 };

Joystick joystick = Joystick(A0, A1, A2);

void setup() {
  Serial.begin(9600);
}

void loop()  {
  joystick.readInto(payload);

  
  delay(100);
}

