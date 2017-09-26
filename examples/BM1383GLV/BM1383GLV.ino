/*
 * BM1383GLV example
 * 
 * This sketch shows you how to correctly measure pressure using BM1383GLV
 * 
 * Before powering up your Arduino, make sure to select 1.8V or 3V on jumper J15 on the shield!
 */

// define the sensor we will use
#define INCLUDE_BM1383GLV

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class
BM1383GLV sensorPress;

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize the sensor with default settings
  sensorPress.init();

  Serial.println("p[hPa]");
}

void loop() {
  // measure the sensor value
  sensorPress.measure();

  // print the value to the serial port
  Serial.println(sensorPress.pres);

  // wait 100 ms before the next measurement
  delay(100);
}
