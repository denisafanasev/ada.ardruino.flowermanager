/*
 * Led controler implementation library
 * For component AMP-X011 (http://amperka.ru/product/bicolor-led-5mm)
 *
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */

#ifndef BLED_H
#define BLED_H

#include <Arduino.h>

class BLED {
  private:
    uint8_t _color;
    uint8_t _redPin, _greenPin;

  public:
    BLED(uint8_t redPin, uint8_t greenPin);
    void setColor(uint8_t toColor);
    uint8_t getColor();
};

#endif
