/*
 * Pressure sencor controler definition library
 * For component: AMP-X125 (http://amperka.ru/product/force-resistor-12mm)
 *
 * Created by ADA, October 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include <Arduino.h>

class PRESSURESENSOR{
  private:
    uint8_t  _dataPin;

  public:
    PRESSURESENSOR(uint8_t toDataPin);
    int value();
};


#endif

