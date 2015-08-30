/*
 * CALSS IMPLEMENTATION SECTION
 */

#include "RGBLED.h"

// constructor implementation
RGBLED::RGBLED(uint8_t toRedPin, uint8_t toGreenPin, uint8_t toBluePin) {

  _redPin = constrain(toRedPin,0,13);
  _greenPin = constrain(toGreenPin,0,13);
  _bluePin = constrain(toBluePin,0,13);

  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);
}

void RGBLED::setColor(int roRed, int toGreen, int toBlue)
{
  analogWrite(_redPin, constrain(roRed, 0, 255));
  analogWrite(_greenPin, constrain(toGreen, 0, 255));
  analogWrite(_bluePin, constrain(toBlue, 0, 255));
}


