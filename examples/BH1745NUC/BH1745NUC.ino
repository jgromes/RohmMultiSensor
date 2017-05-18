/*
 * BH1745NUC example
 * 
 * This sketch shows you how to correctly detect colors using BH1745NUC
 * 
 * Before powering up your Arduino, make sure to select 3V on jumper J15 on the shield!
 */

// define the sensor we will use
#define INCLUDE_BH1745NUC

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class
BH1745NUC rgbc;

void setup() {
 // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize the sensor with default settings
  rgbc.init();

  Serial.println("R[-]\tG[-]\tB[-]\tC[-]");
}

void loop() {
  // measure the sensor values
  unsigned int* rgbcValue = rgbc.measure();

  // print the values to the serial port
  Serial.print(rgbcValue[0]);
  Serial.print('\t');
  Serial.print(rgbcValue[1]);
  Serial.print('\t');
  Serial.print(rgbcValue[2]);
  Serial.print('\t');
  Serial.println(rgbcValue[3]);

  // safely deallocate memory allocated for the dynamic array 'rgbcValue'
  delete[] rgbcValue;

  // wait 100 ms before the next measurement
  delay(100);
}
