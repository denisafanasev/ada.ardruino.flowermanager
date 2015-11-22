/*
 * Double Color Led controler definition library
 * For component: simple LED
 *
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#ifndef LED_h
#define LED_h

#include <Arduino.h>

class LED {
  private:
    uint8_t  _dataPin;
    bool     _isOn;

  public:
    // constructor
    LED(uint8_t dataPin);

    // switch led on
    void on();

    // switch led off
    void off();

    // led status
    bool isOn();
};

#endif

