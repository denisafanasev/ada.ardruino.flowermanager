/*
 * FLOWER MANAGER PROGRAMM for Arduino Uno board to manage flower's sensors and control water pomp
 * Created by ADA, August 2015
 * version 1.0, available under AGRPLv3 license
 */

#include "LED.h"
#include "BLED.h"
#include "RGBLed.h"
#include "LightSensor.h"

/*
SETUP COMPONET'S PINS LAYOUT
*/

//sensors
#define SENSOR_LIGHT_DATAPIN           0       // Light sensor data pin
#define SENSOR_TEMP_DATAPIN            1       // temperature sensor data pin
#define SENSOR_WET_DATAPIN             2       // wet sensor data pin
#define SENSOR_WATER_DATAPIN           3       // presure sensor data pin

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
const int DARK_LEVEL =                 1000;   // value of light sensor for board of dark, if more then full dark
const int DARKNESS_LEVEL =             800;    // value of light sensor for board of darkness, if less then sun

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

void setup() {
  // serial port init

  if (DEBUG) {
    Serial.begin(9600);
  }

  lightLed.setColor(2);
//  temperatureLed.setColor(1);
//  humidityLed.setColor(1);
//  waterTankLed.setColor(1);

}
// ----- end initials functions -------

// MAIN PROGRAMM
void loop() {
  if (lightSensor.value() < 700) {  //sun
    rgbLed.setColor(0, 255, 0);
  } else {
    if (lightSensor.value() > 900) { //dark
      rgbLed.setColor(255, 0, 0);
    } else { //darkness
      rgbLed.setColor(0, 0, 255);
    }
  }
}
