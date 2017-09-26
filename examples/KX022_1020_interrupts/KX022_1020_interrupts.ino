/*
 * KX022-1020 example
 * 
 * This sketch shows you how to correctly measure acceleration using KX022-1020 accelerometer with interrupts.
 * 
 * Before powering up your Arduino, make sure to select 1.8V or 3V on jumper J15 on the shield!
 */

// define the sensor we will use
#define INCLUDE_KX022_1020

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class using interrupt 0
KX022_1020 sensorAcc(INT_0);
// if you want to use interrupt 1, use the following
// KX022_1020 sensorAcc(INT_1);

// define the interrupt service routine
void acc_isr(void) {
  sensorAcc.setFlagDrdy();
}

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize KX022-1020 with the default values
  // we have to provide the interrupt service routine to the .init() method
  sensorAcc.init(acc_isr);

  Serial.println("X[g]\tY[g]\tZ[g]");
}

void loop() {
  // measure the sensor values
  if(sensorAcc.measure() == 0) {
    // if the values were successfully measured, print them to the serial port
    Serial.print(sensorAcc.accelX);
    Serial.print('\t');
    Serial.print(sensorAcc.accelY);
    Serial.print('\t');
    Serial.println(sensorAcc.accelZ);
  }

  // wait 100 ms before the next measurement
  delay(100);
}
