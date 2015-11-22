/*
 * FLOWER MANAGER PROGRAMM for Arduino Uno board to manage flower's sensors and control water pomp
 * Created by ADA, August 2015
 * version 1.0, available under AGRPLv3 license
 */

#include "LED.h"
#include "BLED.h"
#include "PUMP.h"
#include "RGBLed.h"
#include "LightSensor.h"
#include "HumiditySensor.h"
#include "PressureSensor.h"
#include "TemperatureSensor.h"
/*
SETUP COMPONET'S PINS LAYOUT
*/

//sensors
#define SENSOR_LIGHT_DATAPIN           0       // Light sensor data pin
#define SENSOR_TEMP_DATAPIN            1       // temperature sensor data pin

#define SENSOR1_HUMIDITY_DATAPIN       5       // wet sensor data pin
#define SENSOR1_HUMIDITY_SWITCHPIN     5       // wet sensor switch pin

#define SENSOR_WATERTANK_DATAPIN       4       // presure sensor data pin

// leds
#define  LED_LIGHT_ALARM_REDPIN        12      // light indicator - if light dusring 24h enoght for flower
#define  LED_LIGHT_ALARM_GREENPIN      3       // light indicator - if light dusring 24h enoght for flower

#define  LED_WET_ALARM_REDPIN          8       // light indicator is earth is wet ehoght for flower
#define  LED_WET_ALARM_GREENPIN        2       // light indicator is earth is wet ehoght for flower

#define  LED_TEMP_ALARM_REDPIN         7       // lingt indicator if temp is ok for flower
#define  LED_TEMP_ALARM_GREENPIN       1       // lingt indicator if temp is ok for flower

#define  LED_WATER_ALARM_REDPIN        6       // light indicator if water is in watertank
#define  LED_WATER_ALARM_GREENPIN      0       // light indicator if water is in watertank

// GRB leds
#define RGB_LIGHT_REDPIN               9
#define RGB_LIGHT_GREENPIN             11
#define RGB_LIGHT_BLUEPIN              10

// sounds
//#define SOUND_DATAPIN                  5       // sound device

//mechanics
#define PUMP_DATAPIN                   4       // water pomp data pin

// system's constant
const int LOOP_F =                     1000;   // loop run frequency


const bool DEBUG =                     false;   // if debug mode on for all activities
const bool DEBUG_LIGHT =               false;   // trace light sensor activity
const bool DEBUG_TEMP =                false;   // trace light sensor activity
const bool DEBUG_SOIL =                false;   // trace light sensor activity
const bool DEBUG_WATER =               false;   // trace light sensor activity




// enviroment's constants
const int DARK_LEVEL =                 800;     // value of light sensor for board of dark, if more then full dark
const int DARKNESS_LEVEL =             400;     // value of light sensor for board of darkness, if less then sun
const int HUMIDITY_LOW_LEVEL =         600;     // value of soil dryness
const int HUMIDITY_HIGH_LEVEL =        800;     // level of soil wet
const int WATER_TIME =                 2000;    // time for water on
const int WATER_LEVEL =                500;     // water level in water tank
const int TEMP_MIN =                   17;      // min temperature
const int TEMP_MAX =                   28;      // max temperature
const unsigned long soilInterval =     900000;  // soil humidity check interval (15 min)

/*
VARIABLE DEFINITION SECTION
*/

// objects for leds creation
BLED lightLed(LED_LIGHT_ALARM_REDPIN, LED_LIGHT_ALARM_GREENPIN);        // object instance for light led alarm
BLED temperatureLed(LED_TEMP_ALARM_REDPIN, LED_TEMP_ALARM_GREENPIN);    // object instance for temp led alarm
BLED humidityLed(LED_WET_ALARM_REDPIN, LED_WET_ALARM_GREENPIN);         // object instance for wet led alarm
BLED waterTankLed(LED_WATER_ALARM_REDPIN, LED_WATER_ALARM_GREENPIN);    // object instance for water level led alarm

RGBLED rgbLed(RGB_LIGHT_REDPIN, RGB_LIGHT_GREENPIN, RGB_LIGHT_BLUEPIN); // rgb led for light level control

// objects for sensor
LIGHTSENSOR lightSensor(SENSOR_LIGHT_DATAPIN);                                          // light sensor init
PRESSURESENSOR pressureSensor(SENSOR_WATERTANK_DATAPIN);                                // presure sensor for water lavel control
TEMPERATURESENSOR temperatureSensor(SENSOR_TEMP_DATAPIN);                               // temperature sensor
HUMIDITYSENSOR humiditySensor(SENSOR1_HUMIDITY_DATAPIN, SENSOR1_HUMIDITY_SWITCHPIN);    // soil humidity sensor

// objects for devices
PUMP pumpDevice(PUMP_DATAPIN);                                          //water pump

// internal variables
int _lightLevel = 0;
int _waterLevel = 0;
int _humidityValue = 0;
int _tempValue = 0;

bool _isSun = false;
bool _isDry = true;
bool _isWater = false;

unsigned long currTime = 0;
unsigned long prevSoilTime = 0;

void setup() {
  // serial port init

  if (DEBUG || DEBUG_WATER || DEBUG_SOIL || DEBUG_TEMP || DEBUG_LIGHT) {
    Serial.begin(9600);
  }

  lightLed.setColor(0);
  humidityLed.setColor(0);
  temperatureLed.setColor(0);
  waterTankLed.setColor(0);

  lightLed.blickRed();
  humidityLed.blickRed();
  temperatureLed.blickRed();
  waterTankLed.blickRed();
}
// ----- end initials functions -------

// MAIN PROGRAMM
void loop() {

  // light check ---------------------------------------
  _lightLevel = lightSensor.value();


  if (DEBUG) {
    Serial.println(" ");
    Serial.println(" -> loop trace start <-");
  }
  
  if (DEBUG || DEBUG_LIGHT) {
    Serial.print("Light sensor value: ");
    Serial.println(_lightLevel);
    Serial.print("Light level detected: ");
  }

  if (_lightLevel < DARKNESS_LEVEL) {  //sun

    if (DEBUG || DEBUG_LIGHT) {
      Serial.println("SUN");
    }

    _isSun = true;
    rgbLed.setColor(0, 125, 0);

  } else {

    _isSun = false;

    if (_lightLevel > DARK_LEVEL) { //dark

      rgbLed.setColor(125, 0, 0);

      if (DEBUG || DEBUG_LIGHT) {
        Serial.println("DARK");
      }

    } else { //darkness

      if (DEBUG || DEBUG_LIGHT) {
        Serial.println("DARKNESS");
      }

      rgbLed.setColor(0, 0, 125);
    }
  }

  lightLed.setColor(2);
  //----------------------------------

  // water level check
  _waterLevel = pressureSensor.value();


  if (DEBUG || DEBUG_WATER) {
    Serial.print("Water lever sensor value: ");
    Serial.println(_waterLevel);
    Serial.print("Water level detected: ");
  }


  if (_waterLevel > WATER_LEVEL) {
    _isWater = true;
    waterTankLed.setColor(2);

    if (DEBUG || DEBUG_WATER) {
      Serial.println("HIGH");
    }
  } else {
    _isWater = false;
    waterTankLed.setColor(1);

    if (DEBUG || DEBUG_WATER) {
      Serial.println("LOW");
    }
  }
  // ---------------------------------

  // temperature  check
  _tempValue = temperatureSensor.value();


  if (DEBUG || DEBUG_TEMP) {
    Serial.print("Temp sensor value: ");
    Serial.println(_tempValue);
    Serial.print("Temp level detected: ");
  }


  if (_tempValue > TEMP_MAX) {
    temperatureLed.setColor(1);

    if (DEBUG || DEBUG_TEMP) {
      Serial.println("HIGH");
    }
  } else {
    if (_tempValue < TEMP_MIN) {
      temperatureLed.setColor(1);

      if (DEBUG || DEBUG_TEMP) {
        Serial.println("LOW");
      }
    }
    else {
      temperatureLed.setColor(2);

      if (DEBUG || DEBUG_TEMP) {
        Serial.println("NORM");
      }
    }
  }

  // ---------------------------------

  // humidity soil check -------------
  currTime = millis(); // current time

  if (currTime < prevSoilTime) {
    prevSoilTime = 0;
  }

  if ((currTime - prevSoilTime > soilInterval) || (prevSoilTime == 0)) {
    prevSoilTime = currTime;

    if (DEBUG || DEBUG_SOIL) {
      Serial.print("Soil humidity sensor value: ");
    }

    _humidityValue = humiditySensor.value();

    if (DEBUG || DEBUG_SOIL) {
      Serial.println(_humidityValue);
      Serial.print("Soil humidity level detected: ");
    }

    if (_humidityValue < HUMIDITY_LOW_LEVEL) {
      _isDry = true;
      humidityLed.setColor(1);

      if (DEBUG || DEBUG_SOIL) {
        Serial.println("DRY");
      }
    } else {
      _isDry = false;
      humidityLed.setColor(2);

      if (DEBUG || DEBUG_SOIL) {
        Serial.println("WET");
      }
    }
    //----------------------------------

    // action section
    if (_isSun && _isDry && _isWater) {
      pumpDevice.on(WATER_TIME);
    }
  }

  // end action point

  delay(LOOP_F);

}

