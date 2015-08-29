/*
 * Double Color Led controler implementation library
 * For component: Ambient Light Sensor by DFRobot
 *
 * Created by ADA, August 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */
#include "LIGHTSENSOR.h"

LIGHTSENSOR::LIGHTSENSOR(uint8_t toDataPin) {
  _dataPin = toDataPin;
}

int LIGHTSENSOR::value() {
  return analogRead(_dataPin);
}
