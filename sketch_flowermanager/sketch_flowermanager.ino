
///*
//   FLOWER MANAGER PROGRAMM for Arduino Uno board to manage flower's sensors and control water pomp
//   Created by ADA, August 2015
//   version 2.0, available under AGRPLv3 license
//*/
//
#include "TroykaDHT11.h"
#include "HumiditySensor.h"
#include "PRESSURESENSOR.h"
#include "LightSensor.h"
#include "StatusRegister.h"

const unsigned long soilInterval =     1800000;  // soil humidity check interval (15 min)
//const unsigned long soilInterval =     1000;  // soil humidity check interval (15 min)

// enviroment's constants
const int DARK_LEVEL =                 800;     // value of light sensor for board of dark, if more then full dark
const int DARKNESS_LEVEL =             400;     // value of light sensor for board of darkness, if less then sun
const int HUMIDITY_LOW_LEVEL =         400;     // value of soil dryness
const int WATER_TIME =                 2000;    // time for water on
const int WATER_LEVEL =                100;     // water level in water tank
const int TEMP_MIN =                   17;      // min temperature
const int TEMP_MAX =                   28;      // max temperature

//device switch
const bool isPumpOn = true;
const bool isHumCheckOn = true;
const bool isWaterCheckOn = true;
const bool isLightCheckOn = true;
const bool isTempCheckOn = false;

int _lightLevel = 0;
int _waterLevel = 0;
float _tempValue = 0;
float _airHumidityValue = 0;
int _humidityValue = 0;

uint8_t _humV = 0;
uint8_t _waterV = 0;
uint8_t _lightV = 0;
uint8_t _tempV = 0;

int toneForValue = 0;

unsigned long currTime = 0;
unsigned long prevSoilTime = 0;

uint8_t TONE_PIN = 5;

STATUSREGISTER statusLeds(2, 3, 4);               // object for shift register with leds and sound

HUMIDITYSENSOR humiditySensor(0);    // soil humidity sensor
PRESSURESENSOR pressureSensor(2);        // presure sensor for water lavel control
LIGHTSENSOR lightSensor(1);              // light sensor init
DHT11 temperatureSensor(7);  // temperature sensor

void reset_all_to_low() {
  for (int i = 2; i <= 13; i++) { //we can't use pin0-1 due to serial communication is used
    pinMode(i, OUTPUT); // all pins to output by default
    digitalWrite(i, LOW); // all pins to low by default
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Device restart");

  Serial.println("Devices initiation....");

  Serial.print("Hum check sensor: ");
  if (isHumCheckOn) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  Serial.print("Pump device: ");
  if (isPumpOn) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  Serial.print("Water level sensor: ");
  if (isWaterCheckOn) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  Serial.print("Ligh level sensor: ");
  if (isLightCheckOn) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  Serial.print("Temp level sensor: ");
  if (isTempCheckOn) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  Serial.println("");
  Serial.println("Devices initiation completed");

  reset_all_to_low();

  //statusLeds.init();
  //humiditySensor.init();
  //pressureSensor.init();
  //lightSensor.init();

  noTone(TONE_PIN);
  //statusLeds.AllOff();
}

void loop() {
  //Serial.println("");
  //Serial.println(" -> loop trace start <-");

  // water level check
  if (isWaterCheckOn) {
    _waterLevel = pressureSensor.value();

    Serial.print("Water lever sensor value: ");
    Serial.println(_waterLevel);
    Serial.print("Water level detected: ");

    if (_waterLevel > WATER_LEVEL) {
      Serial.println("NORMAL");
      statusLeds.waterAlarm(false);
      statusLeds.water(true);
    } else {
      Serial.println("LOW");
      statusLeds.waterAlarm(true);
      statusLeds.water(false);
    }
  } else {
    _waterLevel = WATER_LEVEL + 1;
  }

  // light check ---------------------------------------
  if (isLightCheckOn) {
    _lightLevel = lightSensor.value();

    Serial.print("Light sensor value: ");
    Serial.println(_lightLevel);
    Serial.print("Light level detected: ");

    if (_lightLevel < DARKNESS_LEVEL) {  //sun
      Serial.println("SUN");
      statusLeds.light(true);
    } else {
      if (_lightLevel > DARK_LEVEL) { //dark
        statusLeds.light(false);
        Serial.println("DARK");
      } else { //darkness
        Serial.println("DARKNESS");
        statusLeds.light(false);
      }
    }
  } else {
    _lightLevel = DARKNESS_LEVEL - 1;
  }

  // temperature  check
  if (isTempCheckOn) {
    temperatureSensor.read();
    _tempValue = temperatureSensor.getTemperatureC();
    _airHumidityValue = temperatureSensor.getHumidity();

    Serial.print("Temp sensor value: ");
    Serial.println(_tempValue);
    Serial.print("Temp level detected: ");

    if (_tempValue > TEMP_MAX) {
      Serial.println("HIGH");
      statusLeds.temperature(false);
    } else {
      if (_tempValue < TEMP_MIN) {
        Serial.println("LOW");
        statusLeds.temperature(false);
      } else {
        Serial.println("NORM");
        statusLeds.temperature(true);
      }
    }

    Serial.print("Air humidity sensor value: ");
    Serial.println(_airHumidityValue);
    statusLeds.airHum(true);

  } else {

  }

  // humidity soil check -------------

  currTime = millis(); // current time

  if (currTime < prevSoilTime) {
    prevSoilTime = 0;
  }

  if ((currTime - prevSoilTime > soilInterval) || (prevSoilTime == 0)) {
    prevSoilTime = currTime;

    if (isHumCheckOn) {
      Serial.print("Soil humidity sensor value: ");
      statusLeds.soilHumChecking(true);

      _humidityValue = humiditySensor.value();

      statusLeds.soilHumChecking(false);
      Serial.println(_humidityValue);
      Serial.print("Soil humidity level detected: ");

      if (_humidityValue < HUMIDITY_LOW_LEVEL) {
        Serial.println("DRY");
        statusLeds.soilHum(false);

        if (statusLeds.canWatering()) {
          if (isPumpOn) {
            statusLeds.pump(true);
            delay(WATER_TIME); // идет полив
            statusLeds.pump(false);
          }
        }

      } else {
        Serial.println("WET");
        statusLeds.soilHum(true);
      }
    } else {
      // just do nothing
      _humidityValue = HUMIDITY_LOW_LEVEL + 1;
    }

  }

  // generate a frequency from the sin value
  //  if (_waterV == 1) {
  //    for (int toneForValue = 0; toneForValue < 180; toneForValue++) {
  //      tone(TONE_PIN, 2000 + (int((sin(toneForValue * (3.1412 / 180))) * 1000)));
  //      delay(2);
  //    }
  //  } else {
  //    noTone(TONE_PIN);
  //    toneForValue = 0;
  //  }

  // end action point

}
