/*
 * Pressure sencor controler implementation library
 * For component: AMP-X125 (http://amperka.ru/product/force-resistor-12mm)
 *
 * Created by ADA, October 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */

#include "PRESSURESENSOR.h"

PRESSURESENSOR::PRESSURESENSOR(uint8_t toDataPin) {
  _dataPin = constrain(toDataPin,0,5);    // check for only analog pin range number
}

int PRESSURESENSOR::value() {
  int _value = 0;
  _value = analogRead(_dataPin);
  return _value;
}

