/*
   Led controler based on shift register 74HC595 definition library
   For component: simple LED

   Created by ADA, January 2016
   Version 2.0, available under AGPLv3 lecense

*/
#ifndef STATUSREGISTER_h
#define STATUSREGISTER_h

#include <Arduino.h>

class STATUSREGISTER {
  private:
    
    uint8_t  _dataPin;
    uint8_t  _clockPin;
    uint8_t  _latchPin;

    bool _lightIsOk;
    bool _soilHumIsOk;
    bool _waterLevelIsOk;
    bool _tempIsOk;
    bool _airHumIsOk;
    bool _isSoilHumOn;
    bool _isPumpOn;
    bool _isWaterAlarm;
    bool _isLightAlarm;
    bool _isTempAlarm;

    void setValue();

  public:
    // constructor
    STATUSREGISTER(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin);

    void light(bool isOk);
    void soilHum(bool isOk);
    void water(bool isOk);
    void temperature(bool isOk);
    void airHum(bool isOk);
    void soilHumChecking(bool isOn);
    void pump(bool isOn);
    void waterAlarm(bool isOn);
    void lightAlarm(bool isOn);
    void tempAlarm(bool isOn);
    
    void AllOff();
    void init(); // funy welcome action
    bool isOn(); // led status
    bool canWatering(); // led status
};

#endif

