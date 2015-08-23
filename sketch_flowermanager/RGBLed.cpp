/*
 * CALSS IMPLEMENTATION SECTION
 */

#include "RGBLed.h"

// constructor implementation
RGBLed::RGBLed(uint8_t dataPin):_dataPin(dataPin) {
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
  _isOn = false;
}

// desctructor implementation
RGBLed::~RGBLed() {
  //nothing to destroy
}

void RGBLed::on() {
  digitalWrite(_dataPin, HIGH);
  _isOn = true;
}

void RGBLed::off() {
  digitalWrite(_dataPin, LOW);  
  _isOn = false;
}

bool RGBLed::isOn() {
  return _isOn;
}
