/*
 * All 5.0 V sensors example
 * 
 * This sketch shows you how to use all 5.0 V ROHM sensors simultaneously.
 * These sensors are: BD7411G Hall sensor
 *                    BD1020HFV temperature sensor
 * 
 * Before powering up your Arduino, make sure to select 5V on jumper J15 on the shield!
 * 
 * NOTE: When using BD7411G Hall sensor with Arduino UNO, be sure to disconnect the sensor from the shield before uploading the sketch!
 *       Since BD7411G's OUT pin is directly connected to Arduino D0 (serial RX), any attempt to upload with the sensor connected will lead to avrdude: stk500_getsync() error.
 */

// define all the sensors we will use
#define INCLUDE_ALL_5V0_SENSORS

// include the library
#include <RohmMultiSensor.h>

//instantiate all the sensors' classes
BD7411G hall;
BD1020HFV temp;

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize all the sensor with default settings
  hall.init();
  temp.init();

  Serial.println("MF[-]\tt[dg C]");
}

void loop() {
  // measure all the sensor values
  bool magFieldDetected = hall.measure();
  float tempValue = temp.measure();

  // print the values to the serial port
  Serial.print(magFieldDetected);
  Serial.print('\t');
  Serial.println(tempValue);

  // wait 100 ms before the next measurement
  delay(100);
}
