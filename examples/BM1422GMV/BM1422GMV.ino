/*
 * BM1422GMV example
 * 
 * This sketch shows you how to correctly measure magnetic induction using BM1422GMV magnetometer.
 * 
 * Before powering up your Arduino, make sure to select 1.8V on jumper J15 on the shield!
 */

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class using interrupt 0
BM1422GMV sensorMag(INT_0);
// if you want to use interrupt 1, use the following
// BM1422GMV sensorMag(INT_1);

// define the interrupt service routine
void mag_isr(void) {
  sensorMag.setFlagDrdy();
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
  sensorMag.init(mag_isr);

  Serial.println("X[uT]\tY[uT]\tZ[uT]");
}

void loop() {
  // measure the sensor values
  if(sensorMag.measure() == 0) {
    // if the values were successfully measured, print them to the serial port
    Serial.print(sensorMag.magX);
    Serial.print('\t');
    Serial.print(sensorMag.magY);
    Serial.print('\t');
    Serial.println(sensorMag.magZ);
  }

  // wait 100 ms before the next measurement
  delay(100);
}
