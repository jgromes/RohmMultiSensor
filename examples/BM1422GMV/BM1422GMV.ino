/*
 * BM1422GMV example
 * 
 * This sketch shows you how to correctly measure magnetic induction using BM1422GMV magnetometer.
 * 
 * Before powering up your Arduino, make sure to select 1.8V on jumper J15 on the shield!
 */

// define the sensor we will use
#define INCLUDE_BM1422GMV

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class using interrupt 0
BM1422GMV mag(INT_0);
// if you want to use interrupt 1, use the following
// BM1422GMV mag(INT_1);

// define the interrupt service routine
void mag_isr(void) {
  mag.setFlagDrdy();
}

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize the sensor with default settings
  // we have to provide the interrupt service routine to the .init() method
  mag.init(mag_isr);

  Serial.println("X[uT]\tY[uT]\tZ[uT]");
}

void loop() {
  // measure the sensor values
  if(mag.measure() == 0) {
    // if the values were successfully measured, print them to the serial port
    Serial.print(mag.x);
    Serial.print('\t');
    Serial.print(mag.y);
    Serial.print('\t');
    Serial.println(mag.z);
  }

  // wait 100 ms before the next measurement
  delay(100);
}
