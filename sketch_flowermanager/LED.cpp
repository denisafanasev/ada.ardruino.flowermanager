/*
 * Led controler implementation library
 * For component AMP-X011 (http://amperka.ru/product/bicolor-led-5mm) 
 * 
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 * 
 */
#include "LED.h"

// constructor implementation
LED::LED(uint8_t dataPin) {
  _dataPin = dataPin;
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
  _isOn = false;
}

// desctructor implementation
LED::~LED() {
  //nothing to destroy
}

void LED::on() {
  digitalWrite(_dataPin, HIGH);
  _isOn = true;
}

void LED::off() {
  digitalWrite(_dataPin, LOW);  
  _isOn = false;
}

bool LED::isOn() {
  return _isOn;
}
