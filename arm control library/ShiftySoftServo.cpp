#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
 
#include "ShiftySoftServo.h"
#include <Shifty.h> // https://github.com/johnnyb/Shifty

ShiftySoftServo::ShiftySoftServo(void) {
  isAttached = false;
  servoPin = 255;
  angle = 90;
}

void ShiftySoftServo::attach(uint8_t pin) {
  servoPin = pin;
  angle = 90;
  isAttached = true;
}

void ShiftySoftServo::detach(void) {
  isAttached = false;
}

boolean  ShiftySoftServo::attached(void) {
  return isAttached;
}

void ShiftySoftServo::write(uint8_t a) {
  angle = a;

  if (! isAttached) return;
  micros = map(a, 0, 180, 1000, 2000);  
}

void ShiftySoftServo::refresh(Shifty shift) {
  shift.writeBit(servoPin, HIGH);
  delayMicroseconds(micros);
  shift.writeBit(servoPin, LOW);
}
