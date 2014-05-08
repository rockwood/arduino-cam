
const int JOY_STICK_PIN_X = A0;
const int JOY_STICK_PIN_Y = A1;

const int PAN_TILT_PIN_UP = 11;
const int PAN_TILT_PIN_DOWN = 10;
const int PAN_TILT_PIN_LEFT = 9;
const int PAN_TILT_PIN_RIGHT = 6;

const int LANC_WRITE_PIN = 2;
const int LANC_READ_PIN = 3;
const int POT_PIN = A2;

int cmdRepeatCount = 5;
int bitDuration = 104; //Duration of one LANC bit in microseconds. 

boolean ZOOM_IN_4[] = {LOW,LOW,HIGH,LOW,HIGH,LOW,LOW,LOW,   LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW}; //28 08
boolean ZOOM_OUT_4[] = {LOW,LOW,HIGH,LOW,HIGH,LOW,LOW,LOW,   LOW,LOW,LOW,HIGH,HIGH,LOW,LOW,LOW}; //28 18

int responseDelay = 20;
 
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
    lancCommand(ZOOM_IN_4);
  }
  
  else if (currentPot < -100) {
    lancCommand(ZOOM_OUT_4);
  }
  
   delay(responseDelay);
}

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

void lancCommand(boolean lancBit[]) {
  cmdRepeatCount = 0;

  while (cmdRepeatCount < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(LANC_READ_PIN, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }
    
    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bitDuration);  //wait START bit duration
    
    //Write the 8 bits of byte 0 
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    for (int i=7; i>-1; i--) {
      digitalWrite(LANC_WRITE_PIN, lancBit[i]);  //Write bits. 
      delayMicroseconds(bitDuration); 
    }
   
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(LANC_WRITE_PIN, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1
    
    while (digitalRead(LANC_READ_PIN)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bitDuration);  //wait START bit duration
      
    //Write the 8 bits of Byte 1
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    for (int i=15; i>7; i--) {
      digitalWrite(LANC_WRITE_PIN,lancBit[i]);  //Write bits 
      delayMicroseconds(bitDuration);
    }
 
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(LANC_WRITE_PIN, LOW); 

    cmdRepeatCount++;  //increase repeat count by 1
   
    // Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
    // and just wait for the next start bit after a long pause to send the first two command bytes again.
  }//While cmdRepeatCount < 5
}


