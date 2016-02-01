///*
//   FLOWER MANAGER PROGRAMM for Arduino Uno board to manage flower's sensors and control water pomp
//   Created by ADA, August 2015
//   version 2.0, available under AGRPLv3 license
//*/
//

#include "HumiditySensor.h"
#include "COOLER_FAN.h"
#include "LED.h"
#include "PRESSURESENSOR.h"
#include "LightSensor.h"
#include "TEMPERATURESENSOR.h"
#include "PUMP.h"
#include "StatusRegister.h"

const unsigned long soilInterval =     900000;  // soil humidity check interval (15 min)
const int LOOP_F =                     1000;   // loop run frequency

// enviroment's constants
const int DARK_LEVEL =                 800;     // value of light sensor for board of dark, if more then full dark
const int DARKNESS_LEVEL =             400;     // value of light sensor for board of darkness, if less then sun
const int HUMIDITY_LOW_LEVEL =         400;     // value of soil dryness
const int WATER_TIME =                 2000;    // time for water on
const int WATER_LEVEL =                400;     // water level in water tank
const int TEMP_MIN =                   17;      // min temperature
const int TEMP_MAX =                   28;      // max temperature

int _lightLevel = 0;
int _waterLevel = 0;
float _tempValue = 0;
int _humidityValue = 0;

uint8_t _humV = 0;
uint8_t _waterV = 0;
uint8_t _lightV = 0;
uint8_t _tempV = 0;

unsigned long currTime = 0;
unsigned long prevSoilTime = 0;

COOLER_FAN cooler(5);                    // cooler
LED sensorLeds(11, 10, 9);               // object for shift register with leds
STATUSREGISTER statusLeds(8, 7, 6);               // object for shift register with leds and sound
HUMIDITYSENSOR humiditySensor(5, 13);    // soil humidity sensor
PRESSURESENSOR pressureSensor(4);        // presure sensor for water lavel control
LIGHTSENSOR lightSensor(3);              // light sensor init
TEMPERATURESENSOR temperatureSensor(2);  // temperature sensor
PUMP pumpDevice(12);                     // water pump

void reset_all_to_low() {
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void setup() {
  Serial.begin(9600);

  reset_all_to_low();

  cooler.init();
  sensorLeds.init();
  statusLeds.init();
  humiditySensor.init();
  pressureSensor.init();
  lightSensor.init();
  temperatureSensor.init();
  pumpDevice.init();

  sensorLeds.on(1, 1, 1, 1); //setup leds to red colors by default
}

void loop() {
  Serial.println("");
  Serial.println(" -> loop trace start <-");

  // humidity soil check -------------
  currTime = millis(); // current time

  if (currTime < prevSoilTime) {
    prevSoilTime = 0;
  }

  if ((currTime - prevSoilTime > soilInterval) || (prevSoilTime == 0)) {
    prevSoilTime = currTime;
    Serial.print("Soil humidity sensor value: ");
    statusLeds.humCheckOn(true);
    _humidityValue = humiditySensor.value();
    statusLeds.humCheckOn(false);
    Serial.println(_humidityValue);
    Serial.print("Soil humidity level detected: ");

    if (_humidityValue < HUMIDITY_LOW_LEVEL) {
      _humV = 1; //red color of hum led
      Serial.println("DRY");
    } else {
      _humV = 2; //green color of hum led
      Serial.println("WET");
    }
  }

  // water level check
  _waterLevel = pressureSensor.value();

  Serial.print("Water lever sensor value: ");
  Serial.println(_waterLevel);
  Serial.print("Water level detected: ");

  if (_waterLevel < WATER_LEVEL) {
    _waterV = 2;  //green color
    Serial.println("NORMAL");
    statusLeds.noWaterOn(false);
  } else {
    _waterV = 1; //red color
    Serial.println("LOW");
    statusLeds.noWaterOn(true);
  }

  //  // light check ---------------------------------------
  _lightLevel = lightSensor.value();

  Serial.print("Light sensor value: ");
  Serial.println(_lightLevel);
  Serial.print("Light level detected: ");

  _lightV = 2;
  if (_lightLevel < DARKNESS_LEVEL) {  //sun
    Serial.println("SUN");
    //rgbLed.setColor(0, 125, 0);
  } else {
    if (_lightLevel > DARK_LEVEL) { //dark
      _lightV = 1;
      //rgbLed.setColor(125, 0, 0);
      Serial.println("DARK");
    } else { //darkness
      Serial.println("DARKNESS");
      //rgbLed.setColor(0, 0, 125);
    }
  }


  // temperature  check
  _tempValue = temperatureSensor.value();

  Serial.print("Temp sensor value: ");
  Serial.println(_tempValue);
  Serial.print("Temp level detected: ");

  _tempV = 1; 
  if (_tempValue > TEMP_MAX) {
    Serial.println("HIGH");
  } else {
    if (_tempValue < TEMP_MIN) {
      Serial.println("LOW");
    } else {
      _tempV = 2;
      Serial.println("NORM");
    }
  }

  sensorLeds.on(_humV, _waterV, _lightV, _tempV); //setup leds colors

  // action section
  //if (_isSun && _isDry && _isWater) {
  if ((_humV == 1) && (_waterV == 2) && (_lightV == 2)) {
    statusLeds.pumpWorkingOn(true);
    pumpDevice.on(WATER_TIME);
    statusLeds.pumpWorkingOn(false);
  }

  // end action point

  delay(LOOP_F);
}
