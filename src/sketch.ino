const int JOY_STICK_PIN_X = A0;
const int JOY_STICK_PIN_Y = A1;

const int PAN_TILT_PIN_UP = 11;
const int PAN_TILT_PIN_DOWN = 10;
const int PAN_TILT_PIN_LEFT = 9;
const int PAN_TILT_PIN_RIGHT = 6;

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
  Serial.begin(9600);
}

void loop()  {
  int currentJoystickX = readAxis(JOY_STICK_PIN_X);
  int currentJoystickY = readAxis(JOY_STICK_PIN_Y);
  
  Serial.print(currentJoystickX);
  Serial.print("\t");
  Serial.print(currentJoystickY);
  Serial.println();
  
  // Pan
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
  
  // Tilt
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

  delay(responseDelay);
}


