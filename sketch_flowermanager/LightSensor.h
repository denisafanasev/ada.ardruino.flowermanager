/*
 * Double Color Led controler definition library
 * For component: Ambient Light Sensor by DFRobot
 *
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>

class LIGHTSENSOR{
  private:
    uint8_t  _dataPin;

  public:
    LIGHTSENSOR(uint8_t toDataPin);
    int value();
};


#endif

