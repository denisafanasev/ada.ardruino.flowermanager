/*
 * Humidity sencor controler implementation library
 * For component: AMP-B025 (http://amperka.ru/product/soil-moisture-sensor)
 *
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */

#include "HUMIDITYSENSOR.h"

HUMIDITYSENSOR::HUMIDITYSENSOR(uint8_t toDataPin, uint8_t toSwithPin) {
  _dataPin = constrain(toDataPin,0,5);    // check for only analog pin range number
  
  _switchPin = constrain(toSwithPin,0,13);    // check for only analog pin range number
  pinMode(_switchPin, OUTPUT);
  digitalWrite(_switchPin, LOW);
}

int HUMIDITYSENSOR::value() {
  int _value = 0;
  digitalWrite(_switchPin, HIGH);
  delay(1000);
  _value = analogRead(_dataPin);
  digitalWrite(_switchPin, LOW);
  return _value;
}

