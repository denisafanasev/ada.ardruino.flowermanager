/*
 * Double Color Led controler implementation library
 * For component AMP-X011 (http://amperka.ru/product/bicolor-led-5mm) 
 * 
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 * 
 */
#include "DCLed.h"

// constructor implementation
DCLed::DCLed(uint8_t dataPin) {
  _dataPin = dataPin;
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
  _isOn = false;
}

// desctructor implementation
DCLed::~DCLed() {
  //nothing to destroy
}

void DCLed::on() {
  digitalWrite(_dataPin, HIGH);
  _isOn = true;
}

void DCLed::off() {
  digitalWrite(_dataPin, LOW);  
  _isOn = false;
}

bool DCLed::isOn() {
  return _isOn;
}
