
const int joystickPinClick = 2;      
const int joystickPinX = A0;
const int joystickPinY = A1;
const int ledPin = 13;

const int left = 11;
const int right = 3;
const int up = 6;
const int down = 9;

int responseDelay = 20;
int range = 510;
int threshold = 55;
int center = range/2;
 
void setup()
{
  Serial.begin(115200);
}
 
void loop()  {
  int joystickCurrentX = readAxis(joystickPinX);
  int joystickCurrentY = readAxis(joystickPinY);
 
  if (joystickCurrentY > 0)
  {
    analogWrite(up, abs(joystickCurrentY));
    analogWrite(down, 0);
  }
 
  else if (joystickCurrentY < 0)
  {
    analogWrite(down, abs(joystickCurrentY));
    analogWrite(up, 0);
  }
  // Stop tilt
  else
  {
    analogWrite(up, 0);
    analogWrite(down, 0);
  }
 
  // Pan based on the input from the joystick
  if (joystickCurrentX > 0)
  {
    analogWrite(right, abs(joystickCurrentX));
    analogWrite(left, 0);
  }
 
  else if (joystickCurrentX < 0)
  {
    analogWrite(left, abs(joystickCurrentX));
    analogWrite(right, 0);
  }
 
  else
  {
    analogWrite(right, 0);
    analogWrite(left, 0);
  }
  
  Serial.print(joystickCurrentX);
  Serial.print(", ");  
  Serial.print(joystickCurrentY);
  Serial.print(", ");  
  Serial.println();

  delay(responseDelay);
}

int readAxis(int pin) { 
  // read the analog input:
  int reading = analogRead(pin);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  int distance = reading - center;
  
  if (abs(distance) < threshold) {
    distance = 0;
  } 

  // return the distance for this axis:
  return distance;
}
