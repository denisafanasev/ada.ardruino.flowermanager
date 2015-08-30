/*
 * FLOWER MANAGER PROGRAMM for Arduino Uno board to manage flower's sensors and control water pomp
 * Created by ADA, August 2015
 * version 1.0, available under AGRPLv3 license
 */

#include "LED.h"
#include "BLED.h"
#include "RGBLed.h"
#include "LightSensor.h"
#include "HumiditySensor.h"
/*
SETUP COMPONET'S PINS LAYOUT
*/

//sensors
#define SENSOR_LIGHT_DATAPIN           0       // Light sensor data pin
#define SENSOR_TEMP_DATAPIN            1       // temperature sensor data pin
#define SENSOR1_HUMIDITY_DATAPIN       2       // wet sensor data pin
#define SENSOR2_HUMIDITY_DATAPIN       3       // wet sensor data pin
#define SENSOR_WATER_DATAPIN           4       // presure sensor data pin

// leds
#define  LED_LIGHT_ALARM_REDPIN        12      // light indicator - if light dusring 24h enoght for flower
#define  LED_TEMP_ALARM_REDPIN         7       // lingt indicator if temp is ok for flower
#define  LED_WET_ALARM_REDPIN          8       // light indicator is earth is wet ehoght for flower
#define  LED_WATER_ALARM_REDPIN        6       // light indicator if water is in watertank

#define  LED_LIGHT_ALARM_GREENPIN      3       // light indicator - if light dusring 24h enoght for flower
#define  LED_TEMP_ALARM_GREENPIN       1       // lingt indicator if temp is ok for flower
#define  LED_WET_ALARM_GREENPIN        2       // light indicator is earth is wet ehoght for flower
#define  LED_WATER_ALARM_GREENPIN      0       // light indicator if water is in watertank

// GRB leds
#define RGB_LIGHT_REDPIN               9
#define RGB_LIGHT_GREENPIN             11
#define RGB_LIGHT_BLUEPIN              10

// sounds
#define SOUND_DATAPIN                  5       // sound device

//mechanics
#define PUMP_DATAPIN                   4       // water pomp data pin

// system's constant
const int LOOP_F =                     1000;   // loop run frequency
const bool DEBUG =                     false;  // if debug mode on

// enviroment's constants
const int DARK_LEVEL =                 800;   // value of light sensor for board of dark, if more then full dark
const int DARKNESS_LEVEL =             400;    // value of light sensor for board of darkness, if less then sun
const int HUMIDITY_LOW_LEVEL =         450;    // value of soil dryness
const int HUMIDITY_HIGH_LEVEL =        700;    // level of soil wet

/*
VARIABLE DEFINITION SECTION
*/

// objects for leds creation
BLED lightLed(LED_LIGHT_ALARM_REDPIN, LED_LIGHT_ALARM_GREENPIN);        // object instance for light led alarm
BLED temperatureLed(LED_TEMP_ALARM_REDPIN, LED_TEMP_ALARM_GREENPIN);    // object instance for temp led alarm
BLED humidityLed(LED_WET_ALARM_REDPIN, LED_WET_ALARM_GREENPIN);         // object instance for wet led alarm
BLED waterTankLed(LED_WATER_ALARM_REDPIN, LED_WATER_ALARM_GREENPIN);    // object instance for water level led alarm

RGBLED rgbLed(RGB_LIGHT_REDPIN, RGB_LIGHT_GREENPIN, RGB_LIGHT_BLUEPIN);

LIGHTSENSOR lightSensor(SENSOR_LIGHT_DATAPIN);                          // light sensor init
HUMIDITYSENSOR humiditySensor1(SENSOR1_HUMIDITY_DATAPIN);
HUMIDITYSENSOR humiditySensor2(SENSOR2_HUMIDITY_DATAPIN);

int _lightLevel = 0;
int _humidityLevel1 = 0;
int _humidityLevel2 = 0;
int _averageHumidityLevel = 0;

void setup() {
  // serial port init

  if (DEBUG) {
    Serial.begin(9600);
  }

  lightLed.setColor(2);
  humidityLed.setColor(0);
  temperatureLed.setColor(0);
  waterTankLed.setColor(0);

}
// ----- end initials functions -------

// MAIN PROGRAMM
void loop() {

  // light check
  _lightLevel = lightSensor.value();

  if (DEBUG) {
    Serial.println(" -> loop trace start <-");
    Serial.print("Light sensor value: ");
    Serial.println(_lightLevel);
    Serial.print("Light level detected: ");
  }

  if (_lightLevel < DARKNESS_LEVEL) {  //sun
    if (DEBUG) {
      Serial.println("SUN");
    }
    rgbLed.setColor(0, 255, 0);
  } else {
    if (DEBUG) {
      Serial.println("DARKNESS");
    }

    if (_lightLevel > DARK_LEVEL) { //dark
      rgbLed.setColor(255, 0, 0);
    } else { //darkness
      if (DEBUG) {
        Serial.println("DARK");
      }

      rgbLed.setColor(0, 0, 255);
    }
  }

  // soil humidity check
  _humidityLevel1 = humiditySensor1.value();
  _humidityLevel2 = humiditySensor2.value();

  if (DEBUG) {
    Serial.print("Soil humidity sensor value 1: ");
    Serial.println(_humidityLevel1);
    Serial.print("Soil humidity sensor value 2: ");
    Serial.println(_humidityLevel2);
  }

  _averageHumidityLevel = (int)round((_humidityLevel1 + _humidityLevel2) / 2);

  if (DEBUG) {
    Serial.print("Soil humidity average value: ");
    Serial.println(_averageHumidityLevel);
    Serial.print("Humidity level detected: ");
  }

  if (_averageHumidityLevel < HUMIDITY_LOW_LEVEL) {

    if (DEBUG) {
      Serial.println("DRYNESS");
    }

    humidityLed.setColor(1);
  } else {

    if (_averageHumidityLevel > HUMIDITY_HIGH_LEVEL) {
      if (DEBUG) {
        Serial.println("WET");
      }
    } else {
      if (DEBUG) {
        Serial.println("NORMAL");
      }
    }

    humidityLed.setColor(2);
  }

  if (DEBUG) {
    delay(1000);
  }
}
