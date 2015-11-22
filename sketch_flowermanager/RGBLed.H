#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

class RGBLED {
  private:
    uint8_t  _redPin;
    uint8_t  _greenPin;
    uint8_t _bluePin;

  public:
    // constructor
    RGBLED(uint8_t toRedPin, uint8_t toGreenPin, uint8_t toBluePin);
    void setColor(int roRed, int toGreen, int toBlue);
};

#endif

