/*
 * KX022-1020 example
 * 
 * This sketch shows you how to correctly measure acceleration using KX022-1020 accelerometer wihtout interrupts.
 * 
 * Before powering up your Arduino, make sure to select 1.8V or 3V on jumper J15 on the shield!
 */

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class with default settings
KX022_1020 sensorAcc;
// the above is equivalent to
// KX022_1020 acc(INT_NONE);

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize KX022-1020 with the default values
  sensorAcc.init();

  Serial.println("X[g]\tY[g]\tZ[g]");
}

void loop() {
  // measure the sensor values
  sensorAcc.measure();
  
  // print the values to the serial port
  Serial.print(sensorAcc.accelX);
  Serial.print('\t');
  Serial.print(sensorAcc.accelY);
  Serial.print('\t');
  Serial.println(sensorAcc.accelZ);

  // wait 100 ms before the next measurement
  delay(100);
}
