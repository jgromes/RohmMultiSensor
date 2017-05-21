/*
 * BH1790GLC example
 * 
 * This sketch shows you how to use the BM1790GLC sensor for basic heartbeat reading.
 * Use Serial Plotter to display the result.
 * Place your finger on the sensor to visualize your heartbeat.
 * 
 * Before powering up your Arduino, make sure to select 3V on jumper J15 on the shield!
 * Also, connect the red VLED cable to 5V pin.
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
  pulse.measure();

  // print the values to the serial port
  // use the Serial Plotter to visualize the data
  Serial.print(pulse.ledOn);
  Serial.print('\t');
  Serial.println(pulse.ledOff);

  // wait 100 ms before the next measurement
  delay(100);
}
