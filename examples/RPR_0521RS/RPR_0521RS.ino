/*
 * RPR-0521RS example
 * 
 * This sketch shows you how to correctly measure ambient light and proximity using RPR-0521RS
 * 
 * Before powering up your Arduino, make sure to select 3V on jumper J15 on the shield!
 */

// define the sensor we will use
#define INCLUDE_RPR_0521RS

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class
RPR_0521RS als;

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize the sensor with default settings
  als.init();

  Serial.println("PS[cnt]\tALS[lx]");
}

void loop() {
  // measure the sensor values
  als.measure();

  // print the values to the serial port
  Serial.print(als.ps);
  Serial.print('\t');
  Serial.println(als.als);

  // wait 100 ms before the next measurement
  delay(100);
}
