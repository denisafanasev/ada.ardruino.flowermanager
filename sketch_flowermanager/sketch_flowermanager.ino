/*
 * FLOWER MANAGER PROGRAMM for Arduino Uno board to manage flower's sensors and control water pomp
 * Created by ADA, August 2015
 * version 1.0, available under AGRPLv3 license
 */

#include "LED.h"
#include "RGBLed.h"

/*
SETUP COMPONET'S PINS LAYOUT
*/

//sensors
#define SENSOR_LIGHT_DataPin    0       // Light sensor data pin
#define SENSOR_TEMP_DataPin     1       // temperature sensor data pin
#define SENSOR_WET_DataPin      2       // wet sensor data pin
#define SENSOR_WATER_DataPin    3       // presure sensor data pin

// leds
#define  LED_LIGHT_ALARM        12      // light indicator - if light dusring 24h enoght for flower
#define  LED_TEMP_ALARM         7       // lingt indicator if temp is ok for flower
#define  LED_WET_ALARM          8       // light indicator is earth is wet ehoght for flower
#define  LED_WATER_ALARM        6       // light indicator if water is in watertank

// GRB leds
#define RGB_LIGHT_redPin        9
#define RGB_LIGHT_greenPin      11
#define RGB_LIGHT_bluePin       10

// sounds
#define SOUND_DataPin           5       // sound device

//mechanics
#define WATERPOMP_DataPin       4       // water pomp data pin

// system's constant
const int LOOP_F =              1000;   // loop run frequency
const bool DEBUG =              false;  // if debug mode on

// enviroment's constants
const int DARK_LEVEL =          1000;   // value of light sensor for board of dark, if more then full dark
const int DARKNESS_LEVEL =      800;    // value of light sensor for board of darkness, if less then sun

/*
VARIABLE DEFINITION SECTION
*/

// objects for leds creation
LED led_light(LED_LIGHT_ALARM);       // object instance for light led alarm
LED led_temp(LED_TEMP_ALARM);         // object instance for temp led alarm
LED led_wet(LED_WET_ALARM);           // object instance for wet led alarm
LED led_water(LED_WATER_ALARM);       // object instance for water level led alarm
  
//class LightSensor   // название класса
//{
//  private:
//
//  public:
//    int pin;  // данные - пин подключения датчика, по которому получаем значение датчика
//    int data; // данные - значение датчика
//
//    void SetColor(int red, int green, int blue)
//    {
//      analogWrite(IND_LIGHT_redPin, constrain(red, 0, 255));
//      analogWrite(IND_LIGHT_greenPin, constrain(green, 0, 255));
//      analogWrite(IND_LIGHT_bluePin, constrain(blue, 0, 255));
//    }
//};

int check_light()
{
  int val = 0;
  val = analogRead(SENSOR_LIGHT_DataPin);
  if (DEBUG) Serial.println(val);
  return val;
}
//
//void colorRGB(int IND_LIGHT_redPin, int IND_LIGHT_greenPin, int IND_LIGHT_bluePin)
//{
//  analogWrite(IND_LIGHT_redPin, constrain(red, 0, 255));
//  analogWrite(IND_LIGHT_greenPin, constrain(green, 0, 255));
//  analogWrite(IND_LIGHT_bluePin, constrain(blue, 0, 255));
//}
//
//// ------ end general functions -------
//
////initial functions
//void light_indicator_init() {
//  pinMode(IND_LIGHT_redPin, OUTPUT);
//  pinMode(IND_LIGHT_greenPin, OUTPUT);
//  pinMode(IND_LIGHT_bluePin, OUTPUT);
//
//  pinMode(IND_LIGHT_ALARM, OUTPUT);
//
//  //initial indication
//  colorRGB(255, 255, 255);
//  led_switch(IND_LIGHT_ALARM, true);
//  delay(1000);
//  colorRGB(0, 0, 0);
//  led_switch(IND_LIGHT_ALARM, false);
//}

void setup() {
  // serial port init
  Serial.begin(9600);
  
//  //light indicator init
//  light_indicator_init();
//
//  //computer communication init

}
// ----- end initials functions -------


// MAIN PROGRAMM
void loop() {

//  if (check_light() < 700) {  //sun
//    colorRGB(0, 255, 0);
//  } else {
//    if (check_light() > 900) { //dark
//      colorRGB(255, 0, 0);
//    } else { //darkness
//      colorRGB(0, 0, 255);
//    }
//  }
//
//  delay(LOOP_F);
 led_light.on();
 led_temp.on();

}
