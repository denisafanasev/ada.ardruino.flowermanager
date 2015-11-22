/*
 * Temperature sensor controler implementation library
 * For component: LM35 (http://www.dfrobot.com/wiki/index.php?title=DFRobot_LM35_Linear_Temperature_Sensor_(SKU:DFR0023))
 *
 * Created by ADA, October 2015
 * Version 1.0, available under AGPLv3 lecense
 *
 */

#include "TEMPERATURESENSOR.h"

/*
 * Constructors
 */
TEMPERATURESENSOR::TEMPERATURESENSOR(uint8_t toDataPin) {
  _dataPin = constrain(toDataPin, 0, 5);  // check for only analog pin range number
}

/*
 * Function Value: return value in celsia degrees
 */
int TEMPERATURESENSOR::value() {
  int _value = 0;
  _value = analogRead(_dataPin);  // read data from sensor
  _value = (500 * _value) / 1024; // convert the voltage to temperture
  return _value;
}

