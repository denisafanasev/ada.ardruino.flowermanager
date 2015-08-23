/*
 * Double Color Led controler definition library
 * For component AMP-X011 (http://amperka.ru/product/bicolor-led-5mm) 
 * 
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 * 
 */
#ifndef DCLed_h
#define DCLed_h

#include <Arduino.h>

class DCLed {
  private:
  
  uint8_t  _dataPin;
  bool     _isOn;

  public:

  // constructor
  DCLed(uint8_t dataPin);

  //dectructor
  ~DCLed();

  // switch led on
  void on();

  // switch led off
  void off();

  // led status
  bool isOn();
};

#endif
