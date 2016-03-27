/*
   Status controler based on shift register 74HC595 implementation library
   For component: cascade is shift registers with LED indicators

   Created by ADA, January 2016
   Version 2.1, available under AGPLv3 lecense

*/

//второй регистр
//0b10000000 - влажность воздуха ок
//0b01000000 - влажность воздуха не ок
//0b00100000 - работает датчик влажности почвы
//0b00010000 - работает помпа
//0b00001000 - нет воды в баке
//0b00000100 - давно нет света
//0b00000010 - плохо с температурой

//первый регистр
//0b10000000 - свет ок
//0b01000000 - свет не ок
//0b00100000 - почва ок
//0b00010000 - почва не ок
//0b00001000 - вода ок
//0b00000100 - вода не ок
//0b00000010 - температура воздуха ок
//0b00000001 - температура воздуха не ок

#include "STATUSREGISTER.h"

// constructor implementation
STATUSREGISTER::STATUSREGISTER(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin) {

  //shift register confiruration
  _dataPin = constrain(dataPin, 0, 13);
  _latchPin = constrain(latchPin, 0, 13);
  _clockPin = constrain(clockPin, 0, 13);

  // выключаем все индикаторы
  AllOff();
}

void STATUSREGISTER::setValue() {

  byte reg1_mask = 0b00000000;
  byte reg2_mask = 0b00000000;

  // --- -- - -  --   первый регистр в каскаде регистров ---- - - -------
  // индикаторы показателей с сенсоров
  if (_lightIsOk) {
    reg1_mask = reg1_mask | 0b10000000;   // зеленый цвет индикатора значения сенсора освещенности
  } else {
    reg1_mask = reg1_mask | 0b01000000;   // красный цвет индикатора значеня сенсора освещенности
  }

  if (_soilHumIsOk) {
    reg1_mask = reg1_mask | 0b00100000;   // зеленый цвет индикатора значения сенсора влажности почвы
  } else {
    reg1_mask = reg1_mask | 0b00010000;   // красный цвет индикатора значеня сенсора влажности почвы
  }

  if (_waterLevelIsOk) {
    reg1_mask = reg1_mask | 0b00001000;   // зеленый цвет индикатора значения сенсора уровня воды в баке
  } else {
    reg1_mask = reg1_mask | 0b00000100;   // красный цвет индикатора значеня сенсора уровня воды в баке
  }

  if (_tempIsOk) {
    reg1_mask = reg1_mask | 0b00000010;   // зеленый цвет индикатора значения сенсора температуры воздуха
  } else {
    reg1_mask = reg1_mask | 0b01000001;   // красный цвет индикатора значеня сенсора температуры воздуха
  }

  // - -----   -   второй регистр в каскаде - -----
  // индикаторы показателей с сенсоров
  if (_airHumIsOk) {
    reg2_mask = reg2_mask | 0b10000000;   // зеленый цвет индикатора значения сенсора влажности воздуха
  } else {
    reg2_mask = reg2_mask | 0b01000000;   // красный цвет индикатора значеня сенсора влажности воздуха
  }

  // индикаторы работы внешних устройств
  if (_isSoilHumOn) {
    reg2_mask = reg2_mask | 0b00100000; // работает проверка влажности почвы
  }
  if (_isPumpOn) {
    reg2_mask = reg2_mask | 0b00010000; // работает помпа полива
  }

  // индикаторы критических состояний
  if (_isWaterAlarm) {
    reg2_mask = reg2_mask | 0b00001000; // нет воды в баке
  }
  if (_isLightAlarm) {
    reg2_mask = reg2_mask | 0b00000100; // критический уровень освещенности
  }
  if (_isTempAlarm) {
    reg2_mask = reg2_mask | 0b00000010; // критический диаппазон температуры
  }

  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST, reg2_mask);
  shiftOut(_dataPin, _clockPin, LSBFIRST, reg1_mask);
  digitalWrite(_latchPin, HIGH);
}

void STATUSREGISTER::init() {
  pinMode(_dataPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  AllOff();
}

void STATUSREGISTER::AllOff() {
  // register 1
  _lightIsOk = false;
  _soilHumIsOk = false;
  _waterLevelIsOk = false;
  _tempIsOk = false;

  // register 2
  _airHumIsOk = false;
  _isSoilHumOn = false;
  _isPumpOn = false;
  _isWaterAlarm = false;
  _isLightAlarm = false;
  _isTempAlarm = false;

  setValue();
}

bool STATUSREGISTER::isOn() {
  return _lightIsOk || _soilHumIsOk || _waterLevelIsOk || _tempIsOk || _airHumIsOk || _isSoilHumOn || _isPumpOn || _isWaterAlarm || _isLightAlarm || _isTempAlarm;
}

bool STATUSREGISTER::canWatering() {
  return _lightIsOk and (not _isWaterAlarm) and (not _isTempAlarm);
}

// методы установки значений индикаторов
void STATUSREGISTER::light(bool isOk) {
  _lightIsOk = isOk;
  setValue();
}

void STATUSREGISTER::soilHum(bool isOk) {
  _soilHumIsOk = isOk;
  setValue();
}

void STATUSREGISTER::water(bool isOk) {
  _waterLevelIsOk = isOk;
  setValue();
}

void STATUSREGISTER::temperature(bool isOk) {
  _tempIsOk = isOk;
  setValue();
}

void STATUSREGISTER::airHum(bool isOk) {
  _airHumIsOk = isOk;
  setValue();
}

void STATUSREGISTER::soilHumChecking(bool isOn) {
  _isSoilHumOn = isOn;
  setValue();
}

void STATUSREGISTER::pump(bool isOn) {
  _isPumpOn = isOn;
  setValue();
}

void STATUSREGISTER::waterAlarm(bool isOn) {
  _isWaterAlarm = isOn;
  setValue();
}

void STATUSREGISTER::lightAlarm(bool isOn) {
  _isLightAlarm = isOn;
  setValue();
}

void STATUSREGISTER::tempAlarm(bool isOn) {
  _isTempAlarm = isOn;
  setValue();
}
