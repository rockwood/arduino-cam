#include <Lanc.h>

const int JOY_STICK_PIN_X = A0;
const int JOY_STICK_PIN_Y = A1;

const int PAN_TILT_PIN_UP = 11;
const int PAN_TILT_PIN_DOWN = 10;
const int PAN_TILT_PIN_LEFT = 9;
const int PAN_TILT_PIN_RIGHT = 6;

const int LANC_WRITE_PIN = 2;
const int LANC_READ_PIN = 3;
const int POT_PIN = A2;

Lanc lanc(LANC_READ_PIN, LANC_WRITE_PIN);

int cmdRepeatCount = 5;
int bitDuration = 104; //Duration of one LANC bit in microseconds.

byte lancX2 = 0x28;
byte lancZoomIn4 = 0x08;
byte lancZoomOut4 = 0x18;

int responseDelay = 20;

int readPot(int pin) {
  int range = 510;
  int center = range/2;
  int reading = analogRead(pin);
  reading = map(reading, 0, 1023, 0, range);
  int distance = reading - center;
  return distance;
}

int readAxis(int pin) {
  int range = 510;
  int threshold = 55;
  int center = range/2;
  int reading = analogRead(pin);
  
  reading = map(reading, 0, 1023, 0, range);
  
  int distance = reading - center;
  
  if (abs(distance) < threshold) {
    distance = 0;
  }
  
  // return the distance for this axis:
  return distance;
}

void setup() {
  pinMode(LANC_READ_PIN, INPUT); //listens to the LANC line
  pinMode(LANC_WRITE_PIN, OUTPUT); //writes to the LANC line
  
  delay(5000); //Wait for camera to power up completly
  bitDuration = bitDuration - 8; //Writing to the digital port takes about 8 microseconds so only 96 microseconds are left for each bit
  
  Serial.begin(115200);
}

void loop()  {
  // Pan/Tilt
  int currentJoystickX = readAxis(JOY_STICK_PIN_X);
  int currentJoystickY = readAxis(JOY_STICK_PIN_Y);
  
  if (currentJoystickX > 0) {
    analogWrite(PAN_TILT_PIN_RIGHT, abs(currentJoystickX));
    analogWrite(PAN_TILT_PIN_LEFT, 0);
  }
  else if (currentJoystickX < 0) {
    analogWrite(PAN_TILT_PIN_LEFT, abs(currentJoystickX));
    analogWrite(PAN_TILT_PIN_RIGHT, 0);
  }
  else {
    analogWrite(PAN_TILT_PIN_RIGHT, 0);
    analogWrite(PAN_TILT_PIN_LEFT, 0);
  }
  
  if (currentJoystickY > 0) {
    analogWrite(PAN_TILT_PIN_UP, abs(currentJoystickY));
    digitalWrite(PAN_TILT_PIN_DOWN, 0);
  }
  else if (currentJoystickY < 0) {
    analogWrite(PAN_TILT_PIN_DOWN, abs(currentJoystickY));
    analogWrite(PAN_TILT_PIN_UP, 0);
  }
  else {
    analogWrite(PAN_TILT_PIN_UP, 0);
    analogWrite(PAN_TILT_PIN_DOWN, 0);
  }
  
  int currentPot = readPot(POT_PIN);
  
  if (currentPot > 100) {
    lanc.writePair(lancX2, lancZoomIn4);
  }
  
  else if (currentPot < -100) {
    lanc.writePair(lancX2, lancZoomOut4);
  }
  
  delay(responseDelay);
}


