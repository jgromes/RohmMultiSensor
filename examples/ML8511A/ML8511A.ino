/*
 * ML8511A example
 * 
 * This sketch shows you how to correctly measure UV radiation using ML8511A
 * 
 * Before powering up your Arduino, make sure to select 3V on jumper J15 on the shield!
 */

// define the sensor we will use
#define INCLUDE_ML8511A

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class with the default setting (sensor connected to ANALOG_1)
ML8511A sensorUV;
// the above is equivalent to
// ML8511A sensorUV(ANALOG_1);
// if you have the sensor connected to ANALOG_2, use the following
// ML8511A sensorUV(ANALOG_2);

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // initialize the sensor with default settings
  sensorUV.init();

  Serial.println("UV[mW/cm^2]");
}

void loop() {
  // measure the sensor value
  sensorUV.measure();

  // print the value to the serial port
  Serial.println(sensorUV.uvRad);

  // wait 100 ms before the next measurement
  delay(100);
}
