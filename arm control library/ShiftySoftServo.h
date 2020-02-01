#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Shifty.h> 

class ShiftySoftServo {
 public:
  ShiftySoftServo(void);
  void attach(uint8_t pin);
  void detach();
  boolean attached();
  void write(uint8_t a);
  void refresh(Shifty shift);
 private:
  boolean isAttached;
  uint8_t servoPin, angle;
  uint16_t micros;
};
