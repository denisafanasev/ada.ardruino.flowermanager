/*
   Led controler based on shift register 74HC595 definition library
   For component: simple LED

   Created by ADA, January 2016
   Version 2.0, available under AGPLv3 lecense

*/
#ifndef STATUSREGISTER_h
#define STATUSREGISTER_h

#include <Arduino.h>

const byte _statusMasks[] = {0b01000000, 0b00100000, 0b00010000, 0b00001000}; //setup masks for each led which are connected to shift register

class STATUSREGISTER {
  private:
    uint8_t  _dataPin;
    uint8_t  _clockPin;
    uint8_t  _latchPin;
    bool _isHumOn;
    bool _isPumpOn;
    bool _isWaterOn;
    bool _isLightOn;
    void setValue();
    void setValueByMask(byte mask);

  public:
    // constructor
    STATUSREGISTER(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin);

    void humCheckOn(bool isOn); // switch led on
    void pumpWorkingOn(bool isOn); // pump led on
    void noWaterOn(bool isOn); // no water led on
    void noLightOn(bool isOn); // no light led on
    void AllOff(); // switch led off
    void init(); // funy welcome action
    bool isOn(); // led status
};

#endif

