/*
 * COOLER FAN controler definition library
 * For component: Interl CPU cooler
 *
 * Created by ADA, January 2016
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#ifndef COOLER_FAN_h
#define COOLER_FAN_h

#include <Arduino.h>

class COOLER_FAN {
  private:
    uint8_t  _dataPin;
    bool     _isOn;

  public:
    // constructor
    COOLER_FAN(uint8_t dataPin);
      
    void on(); // switch led on
    void off();  // switch led off
    void init();
    bool isOn(); // cooler fan status
};

#endif
