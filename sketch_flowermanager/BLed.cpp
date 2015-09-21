/*
 * Led controler implementation library
 * For component AMP-X011 (http://amperka.ru/product/bicolor-led-5mm)
 *
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */

#include "BLED.h"

BLED::BLED(uint8_t redPin, uint8_t greenPin) {
  _redPin = constrain(redPin, 0, 13);
  _greenPin = constrain(greenPin, 0, 13);
  _color = 0;
  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  setColor(_color);
}

void BLED::setColor(uint8_t toColor) {
  _color = toColor;
  if (_color == 1) { // Red
    digitalWrite(_redPin, HIGH);
    digitalWrite(_greenPin, LOW);
  } else if (_color == 2) { // Green
    digitalWrite(_redPin, LOW);
    digitalWrite(_greenPin, HIGH);
  } else { // Black
    _color = 0;
    digitalWrite(_redPin, LOW);
    digitalWrite(_greenPin, LOW);
  }
}

uint8_t BLED::getColor() {
  return _color;
}

void BLED::blickRed() {

  digitalWrite(_redPin, HIGH);
  digitalWrite(_greenPin, LOW);

  delay(1000);

  digitalWrite(_redPin, LOW);
  digitalWrite(_greenPin, LOW);
}
