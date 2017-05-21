/*
 * BD7411G example
 * 
 * This sketch shows you how to detect magnetic field using BD7411G
 * 
 * Before powering up your Arduino, make sure to select 5V on jumper J15 on the shield!
 */

// define all the sensors we will use
#define INCLUDE_BD7411G

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class
BD7411G hall;

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize the sensor with default settings
  hall.init();
}

void loop() {
  // measure the sensor value
  hall.measure();
  
  // if a magnetic field is detected, print to serial
  if(hall.mf) {
    Serial.println("Magnetic field detected!");
  }

  // wait 100 ms before the next measurement
  delay(100);
}
