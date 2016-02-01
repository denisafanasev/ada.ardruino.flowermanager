/*
   Led controler implementation library
   For component: Intel CPU cooler

   Created by ADA, Janjury 2016
   Version 1.0, available under AGPLv3 lecense

*/
#include "COOLER_FAN.h"

// constructor implementation
COOLER_FAN::COOLER_FAN(uint8_t dataPin) {
  _dataPin = constrain(dataPin, 0, 13);
  _isOn = false;
}

void COOLER_FAN::init() {
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
}

void COOLER_FAN::on() {
  digitalWrite(_dataPin, LOW);
  _isOn = true;
}

void COOLER_FAN::off() {
  digitalWrite(_dataPin, HIGH);
  _isOn = false;
}

bool COOLER_FAN::isOn() {
  return _isOn;
}
