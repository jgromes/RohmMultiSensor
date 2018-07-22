/*
 * BD1020HFV example
 * 
 * This sketch shows you how to correctly measure temperature using BD1020HFV
 * 
 * Before powering up your Arduino, make sure to select 3V or 5V on jumper J15 on the shield!
 */

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class with the default setting (sensor connected to ANALOG_1)
BD1020HFV sensorTmp;
// the above is equivalent to
// BD1020HFV sensorTmp(ANALOG_1);
// if you have the sensor connected to ANALOG_2, use the following
// BD1020HFV sensorTmp(ANALOG_2);

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // initialize the sensor with default settings
  sensorTmp.init();
  
  Serial.println("t[dg C]");
}

void loop() {
  // measure the sensor value
  sensorTmp.measure();

  // print the value to the serial port
  Serial.println(sensorTmp.temp);

  // wait 100 ms before the next measurement
  delay(100);
}
