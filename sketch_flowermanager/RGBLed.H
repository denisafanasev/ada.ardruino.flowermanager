#ifndef RGBLed_H
#define RGBLed_H

#include <Arduino.h>

class RGBLed {
  private:
  
  uint8_t  _dataPin;
  bool     _isOn;

  public:

  // constructor
  RGBLed(uint8_t dataPin);

  //dectructor
  ~RGBLed();

  // switch led on
  void on();

  // switch led off
  void off();

  // led status
  bool isOn();
};

#endif
