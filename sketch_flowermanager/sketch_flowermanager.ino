
///*
//   FLOWER MANAGER PROGRAMM for Arduino Uno board to manage flower's sensors and control water pomp
//   Created by ADA, August 2015
//   version 2.0, available under AGRPLv3 license
//*/
//
#include "TroykaDHT11.h"
#include "HumiditySensor.h"
#include "COOLER_FAN.h"
#include "LED.h"
#include "PRESSURESENSOR.h"
#include "LightSensor.h"
#include "PUMP.h"
#include "StatusRegister.h"

const unsigned long soilInterval =     900000;  // soil humidity check interval (15 min)
//const unsigned long soilInterval =     1000;  // soil humidity check interval (15 min)

// enviroment's constants
const int DARK_LEVEL =                 800;     // value of light sensor for board of dark, if more then full dark
const int DARKNESS_LEVEL =             400;     // value of light sensor for board of darkness, if less then sun
const int HUMIDITY_LOW_LEVEL =         500;     // value of soil dryness
const int WATER_TIME =                 2000;    // time for water on
const int WATER_LEVEL =                400;     // water level in water tank
const int TEMP_MIN =                   17;      // min temperature
const int TEMP_MAX =                   28;      // max temperature

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

//PUMP pumpDevice(12);                     // water pump
//SEVO pumpDevice(11);                     // sevo pin:11
//MOVE pumpDevice(12);                     // water pump
//DIST pumpDevice(12);                     // water pump
//BT pumpDevice(12);                     // water pump

void reset_all_to_low() {
  for (int i = 2; i <= 13; i++) { //we can't use pin0-1 due to serial communication is used
    pinMode(i, OUTPUT); // all pins to output by default
    digitalWrite(i, LOW); // all pins to low by default
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Device restart");

  reset_all_to_low();

  statusLeds.init();
  humiditySensor.init();
  pressureSensor.init();
  lightSensor.init();

  noTone(TONE_PIN);
  statusLeds.AllOff();
}

void loop() {
  Serial.println("");
  Serial.println(" -> loop trace start <-");

  // water level check
  _waterLevel = pressureSensor.value();

  Serial.print("Water lever sensor value: ");
  Serial.println(_waterLevel);
  Serial.print("Water level detected: ");

  if (_waterLevel < WATER_LEVEL) {
    //_waterV = 2;  //green color
    Serial.println("NORMAL");
    statusLeds.waterAlarm(false);
    statusLeds.water(true);
  } else {
    //_waterV = 1; //red color
    Serial.println("LOW");
    statusLeds.waterAlarm(true);
    statusLeds.water(false);
  }

  //  // light check ---------------------------------------
  _lightLevel = lightSensor.value();

  Serial.print("Light sensor value: ");
  Serial.println(_lightLevel);
  Serial.print("Light level detected: ");

  //_lightV = 2;
  if (_lightLevel < DARKNESS_LEVEL) {  //sun
    Serial.println("SUN");
    statusLeds.light(true);
  } else {
    if (_lightLevel > DARK_LEVEL) { //dark
      //_lightV = 1;
      statusLeds.light(false);
      Serial.println("DARK");
    } else { //darkness
      Serial.println("DARKNESS");
      statusLeds.light(false);
    }
  }

  // temperature  check
  temperatureSensor.read();
  _tempValue = temperatureSensor.getTemperatureC();
  _airHumidityValue = temperatureSensor.getHumidity();

  Serial.print("Temp sensor value: ");
  Serial.println(_tempValue);
  Serial.print("Temp level detected: ");

  //_tempV = 1;
  if (_tempValue > TEMP_MAX) {
    Serial.println("HIGH");
    statusLeds.temperature(false);
  } else {
    if (_tempValue < TEMP_MIN) {
      Serial.println("LOW");
      statusLeds.temperature(false);
    } else {
      //_tempV = 2;
      Serial.println("NORM");
      statusLeds.temperature(true);
    }
  }

  Serial.print("Air humidity sensor value: ");
  Serial.println(_airHumidityValue);
  statusLeds.airHum(true);


  // humidity soil check -------------
  currTime = millis(); // current time

  if (currTime < prevSoilTime) {
    prevSoilTime = 0;
  }

  if ((currTime - prevSoilTime > soilInterval) || (prevSoilTime == 0)) {
    prevSoilTime = currTime;
    Serial.print("Soil humidity sensor value: ");
    statusLeds.soilHumChecking(true);

    _humidityValue = humiditySensor.value();

    statusLeds.soilHumChecking(false);
    Serial.println(_humidityValue);
    Serial.print("Soil humidity level detected: ");

    if (_humidityValue < HUMIDITY_LOW_LEVEL) {
      //_humV = 1; //red color of hum led
      Serial.println("DRY");
      statusLeds.soilHum(false);

      if (statusLeds.canWatering()) {
        statusLeds.pump(true);
        delay(WATER_TIME); // идет полив
        statusLeds.pump(false);
      }

    } else {
      //_humV = 2; //green color of hum led
      Serial.println("WET");
      statusLeds.soilHum(true);
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
