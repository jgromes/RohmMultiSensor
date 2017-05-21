/*
 * All 5.0 V sensors example
 * 
 * This sketch shows you how to use all 5.0 V ROHM sensors simultaneously.
 * These sensors are: BD7411G Hall sensor
 *                    BD1020HFV temperature sensor
 * 
 * Before powering up your Arduino, make sure to select 5V on jumper J15 on the shield!
 */

// define all the sensors we will use
#define INCLUDE_ALL_5V0_SENSORS

// include the library
#include <RohmMultiSensor.h>

//instantiate all the sensors' classes
BD7411G hall;
BD1020HFV temp;

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize all the sensor with default settings
  hall.init();
  temp.init();

  Serial.println("MF[-]\tt[dg C]");
}

void loop() {
  // measure all the sensor values
  hall.measure();
  temp.measure();

  // print the values to the serial port
  Serial.print(hall.mf);
  Serial.print('\t');
  Serial.println(temp.t);

  // wait 100 ms before the next measurement
  delay(100);
}
