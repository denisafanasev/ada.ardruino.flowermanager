/*
setup initial constans which depends on components layout
*/

// CMP1: light sensor
#define SENSOR_LIGHT_DataPin 0    //Light sensor data pin
#define IND_LIGHT_redPin 9

// CMP2: light status GRB LED pins layout
//#define IND_LIGHT_redPin 9       // the pin that the red LED is attached to
//#define IND_LIGHT_greenPin 11    // the pin that the green LED is attached to
//#define IND_LIGHT_bluePin 10     // the pin that the blue LED is attached to 
//flower_manager_sketchflower_manager_sketch
//// CMP3: light alarm RED LED pin
//#define  IND_LIGHT_ALARM 12

// -----------------------------------------------------------------------------

//setup internal constants
//int DARK_LEVEL = 1000;                //level of darkness
//int LOOP_F = 1000;                     // loop run frequency
//// --------
//
////debug mode
//bool DEBUG = false;
//-----

// class definitions
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

// --- end class definisions ----

//void led_switch(int led_pin, bool light)
//{
//  if (light) {
//    digitalWrite(led_pin, HIGH);
//  } else {
//    digitalWrite(led_pin, LOW);
//  }
//}
//
//int check_light()
//{
//  int val = 0;
//  val = analogRead(SENSOR_LIGHT_DataPin);
//  if (DEBUG) Serial.println(val);
//  return val;
//}
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
//  //light indicator init
//  light_indicator_init();
//
//  //computer communication init
//  Serial.begin(9600);
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

}
