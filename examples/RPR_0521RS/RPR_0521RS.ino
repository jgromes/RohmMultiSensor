/*
 * RPR-0521RS example
 * 
 * This sketch shows you how to correctly measure ambient light and proximity using RPR-0521RS
 * 
 * Before powering up your Arduino, make sure to select 3V on jumper J15 on the shield!
 */

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class
RPR_0521RS sensorAls;

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize the sensor with default settings
  sensorAls.init();

  Serial.println("PS[-]\tALS[lx]");
}

void loop() {
  // measure the sensor values
  sensorAls.measure();

  // print the values to the serial port
  Serial.print(sensorAls.prox);
  Serial.print('\t');
  Serial.println(sensorAls.ambLight);

  // wait 100 ms before the next measurement
  delay(100);
}
