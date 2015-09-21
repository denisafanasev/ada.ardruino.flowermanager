/*
 * Water pump controler definition library
 * For component: AMP-X157 (http://amperka.ru/product/immersible-water-pump?utm_source=proj&utm_campaign=irrigator&utm_medium=wiki)
 *
 * Created by ADA, September 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#ifndef PUMP_h
#define PUMP_h

#include <Arduino.h>

class PUMP {
  private:
    uint8_t  _dataPin;

  public:
    // constructor
    PUMP(uint8_t dataPin);

    // start
    void on(int _delay);
};

#endif
