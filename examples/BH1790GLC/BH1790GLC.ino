/*
 * BH1790GLC example
 * 
 * This sketch shows you how to use the BM1790GLC sensor for basic heartbeat reading (use Serial Plotter to display the result)
 * Place your finger on the sensor to visualize your heartbeat.
 * 
 * Before powering up your Arduino, make sure to select 3V on jumper J15 on the shield!
 * Also, connect the red VLED cable to 5V pin.
 * 
 * NOTE: Make sure that you are not trying to read the data faster than the readCycle frequency.
 *       For example, if you leave the default value, you have to wait at least 1/32 seconds before accessing the sensor again.
 */

// define the sensor we will use
#define INCLUDE_BH1790GLC

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class
BH1790GLC pulse;

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize the sensor with default settings
  pulse.init();
}

void loop() {
  // measure the sensor values
  int* pulseValue = pulse.measure();

  // print the values to the serial port
  // use the Serial Plotter to visualize the data
  Serial.print(pulseValue[0]);
  Serial.print('\t');
  Serial.println(pulseValue[1]);

  // safely deallocate memory allocated for the dynamic array 'magValue'
  delete[] pulseValue;

  // wait 50 ms before the next measurement, see Note for details
  delay(50);
}
