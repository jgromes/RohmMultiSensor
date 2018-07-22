/*
 * BD7411G example
 * 
 * This sketch shows you how to detect magnetic field using BD7411G
 * 
 * Before powering up your Arduino, make sure to select 5V on jumper J15 on the shield!
 */

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class
BD7411G sensorHall;

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // initialize the sensor with default settings
  sensorHall.init();
}

void loop() {
  // measure the sensor value
  sensorHall.measure();
  
  // if a magnetic field is detected, print to serial
  if(sensorHall.magField) {
    Serial.println("Magnetic field detected!");
  }

  // wait 100 ms before the next measurement
  delay(100);
}
