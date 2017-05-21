/*
 * BD1020HFV example
 * 
 * This sketch shows you how to correctly measure temperature using BD1020HFV
 * 
 * Before powering up your Arduino, make sure to select 3V or 5V on jumper J15 on the shield!
 */

// define the sensor we will use
#define INCLUDE_BD1020HFV

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class with the default setting (sensor connected to ANALOG_1)
BD1020HFV temp;
// the above is equivalent to
// BD1020HFV temp(ANALOG_1);
// if you have the sensor connected to ANALOG_2, use the following
// BD1020HFV temp(ANALOG_2);

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize the sensor with default settings
  temp.init();
  
  Serial.println("t[dg C]");
}

void loop() {
  // measure the sensor value
  temp.measure();

  // print the value to the serial port
  Serial.println(temp.t);

  // wait 100 ms before the next measurement
  delay(100);
}
