/*
   Led controler based on shift register 74HC595 implementation library
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

#include "LED.h"

// constructor implementation
LED::LED(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin) {

  //shift register confiruration
  _dataPin = constrain(dataPin, 0, 13);
  _latchPin = constrain(latchPin, 0, 13);
  _clockPin = constrain(clockPin, 0, 13);

  //setup a flag is one of the leds is on
  _isOn = false;
}

void LED::setValue(byte mask) {
  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST, mask);
  digitalWrite(_latchPin, HIGH);
}

void LED::init() {
  pinMode(_dataPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  off();

  //welcome action
  for (int i = 0; i <= sizeof(_leds) - 1; i++) {
    setValue(_leds[i]);
    delay(500);
  }

  off();
}

void LED::on(uint8_t humV, uint8_t waterV, uint8_t lightV, uint8_t tempV) {
  byte mask = 0b00000000;

  if (humV == 1) {
    mask = mask | _leds[0];
  }
  if (humV == 2) {
    mask = mask | _leds[1];
  }

  if (waterV == 1) {
    mask = mask | _leds[2];
  }
  if (waterV == 2) {
    mask = mask | _leds[3];
  }

  if (lightV == 1) {
    mask = mask | _leds[4];
  }
  if (lightV == 2) {
    mask = mask | _leds[5];
  }

  if (tempV == 1) {
    mask = mask | _leds[6];
  }
  if (tempV == 2) {
    mask = mask | _leds[7];
  }

  setValue(mask);
  _isOn = true;
}

void LED::off() {
  setValue(0b00000000);
  _isOn = false;
}

bool LED::isOn() {
  return _isOn;
}

