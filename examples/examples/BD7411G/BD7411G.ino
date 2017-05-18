/*
 * BD7411G example
 * 
 * This sketch shows you how to detect magnetic field using BD7411G
 * 
 * Before powering up your Arduino, make sure to select 5V on jumper J15 on the shield!
 * 
 * NOTE: When using this sensor, be sure to disconnect it before uploading the sketch.
 *       BD7411G outputs HIGH if no magnetic field is present.
 *       Because this sensor is connected directly Arduino D0 (Serial RX),
 *       any attempt to upload with the sensor connected will lead to avrdude: stk500_getsync() error!
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
  // if a magnetic field is detected, print to serial
  if(hall.measure()) {
    Serial.println("Magnetic field detected!");
  }

  // wait 100 ms before the next measurement
  delay(100);
}
