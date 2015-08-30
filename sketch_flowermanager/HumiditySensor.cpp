/*
 * Humidity sencor controler implementation library
 * For component: AMP-B025 (http://amperka.ru/product/soil-moisture-sensor)
 *
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */

#include "HUMIDITYSENSOR.h"

HUMIDITYSENSOR::HUMIDITYSENSOR(uint8_t toDataPin) {
  _dataPin = constrain(toDataPin,0,5);    // check for only analog pin range number
}

int HUMIDITYSENSOR::value() {
   return analogRead(_dataPin);
}
