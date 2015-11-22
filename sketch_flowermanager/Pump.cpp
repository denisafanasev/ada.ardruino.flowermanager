/*
 * Water pump controler implementation library
 * For component: AMP-X157 (http://amperka.ru/product/immersible-water-pump?utm_source=proj&utm_campaign=irrigator&utm_medium=wiki)
 *
 * Created by ADA, September 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#include "PUMP.h"

// constructor implementation
PUMP::PUMP(uint8_t dataPin) {
  _dataPin = constrain(dataPin,0,13);
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
}

void PUMP::on(int _delay) {
  digitalWrite(_dataPin, HIGH);
  delay(_delay);
  digitalWrite(_dataPin, LOW);
}

