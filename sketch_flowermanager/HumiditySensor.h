/*
 * Humidity sencor controler definition library
 * For component: AMP-B025 (http://amperka.ru/product/soil-moisture-sensor)
 *
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include <Arduino.h>

class HUMIDITYSENSOR{
  private:
    uint8_t  _dataPin;
    uint8_t  _switchPin;

  public:
    HUMIDITYSENSOR(uint8_t toDataPin, uint8_t toSwithPin);
    int value();
};


#endif
