/*
 * Temperature sensor controler definition library
 * For component: LM35
 *
 * Created by ADA, October 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <Arduino.h>

class TEMPERATURESENSOR{
  private:
    uint8_t  _dataPin;

  public:
    TEMPERATURESENSOR(uint8_t toDataPin);
    int value();
};


#endif

