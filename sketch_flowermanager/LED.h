/*
   Led controler based on shift register 74HC595 definition library
   For component: simple LED

   Created by ADA, January 2016
   Version 2.0, available under AGPLv3 lecense

*/
#ifndef LED_h
#define LED_h

#include <Arduino.h>

const byte _leds[] = {0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b10000000}; //setup masks for each led which are connected to shift register

class LED {
  private:
    uint8_t  _dataPin;
    uint8_t  _clockPin;
    uint8_t  _latchPin;
    bool     _isOn;
    void setValue(byte mask);

  public:
    // constructor
    LED(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin);

    void on(uint8_t humV, uint8_t waterV, uint8_t lightV, uint8_t tempV); // switch led on
    void off(); // switch led off
    void init(); // funy welcome action
    bool isOn(); // led status
};

#endif

