/*
   Status controler based on shift register 74HC595 implementation library
   For component: simple LED

   Created by ADA, January 2016
   Version 2.0, available under AGPLv3 lecense

*/

// 0 - shiftOut(11, 9, LSBFIRST, 0b01000000); // hum red
// 1 - shiftOut(11, 9, LSBFIRST, 0b00100000); // hum green
// 2 - shiftOut(11, 9, LSBFIRST, 0b00010000); // water red
// 3 - shiftOut(11, 9, LSBFIRST, 0b00001000); // water green
// 4 - shiftOut(11, 9, LSBFIRST, 0b00000100); // light red
// 5 - shiftOut(11, 9, LSBFIRST, 0b00000010); // light green
// 6 - shiftOut(11, 9, LSBFIRST, 0b00000001); // temp red
// 7 - shiftOut(11, 9, LSBFIRST, 0b10000000); // temp green

#include "STATUSREGISTER.h"

// constructor implementation
STATUSREGISTER::STATUSREGISTER(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin) {

  //shift register confiruration
  _dataPin = constrain(dataPin, 0, 13);
  _latchPin = constrain(latchPin, 0, 13);
  _clockPin = constrain(clockPin, 0, 13);

  //setup a flag is one of the leds is on
  _isHumOn = false;
  _isPumpOn = false;
  _isWaterOn = false;
  _isLightOn = false;
}

void STATUSREGISTER::setValue() {

  byte mask = 0b00000000;

  if (_isHumOn) {
    mask = mask | _statusMasks[0];
  }
  if (_isPumpOn) {
    mask = mask | _statusMasks[1];
  }
  if (_isWaterOn) {
    mask = mask | _statusMasks[2];
  }
  if (_isLightOn) {
    mask = mask | _statusMasks[3];
  }
  
  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST, mask);
  digitalWrite(_latchPin, HIGH);
}

void STATUSREGISTER::setValueByMask(byte mask) {
  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST, mask);
  digitalWrite(_latchPin, HIGH);
}

void STATUSREGISTER::init() {
  pinMode(_dataPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  AllOff();

  //welcome action
  for (int i = 0; i <= sizeof(_statusMasks) - 1; i++) {
    setValueByMask(_statusMasks[i]);
    delay(500);
  }

  AllOff();
}

void STATUSREGISTER::humCheckOn(bool isOn) {
  _isHumOn = isOn;
  setValue();
}

void STATUSREGISTER::pumpWorkingOn(bool isOn) {
  _isPumpOn = isOn;  
  setValue();
}

void STATUSREGISTER::noWaterOn(bool isOn) {
   _isWaterOn = isOn;
  setValue();
}

void STATUSREGISTER::noLightOn(bool isOn) {
  _isLightOn = isOn;
  setValue();
}

void STATUSREGISTER::AllOff() {
  _isHumOn = false;
  _isPumpOn = false;
  _isWaterOn = false;
  _isLightOn = false;
  setValue();
}

bool STATUSREGISTER::isOn() {
  return _isHumOn || _isPumpOn || _isWaterOn || _isLightOn;
}
