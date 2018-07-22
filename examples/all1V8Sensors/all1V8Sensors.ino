/*
 * All 1.8 V sensors example
 * 
 * This sketch shows you how to use all 1.8 V ROHM sensors simultaneously.
 * These sensors are: KX022-1020 accelerometer
 *                    BM1383GLV pressure sensor
 *                    BM1422GMV magnetometer
 * 
 * Before powering up your Arduino, make sure to select 1.8V on jumper J15 on the shield!
 * 
 * Interrupt setting: KX022-1020 is connected to I2C_1 and INTR1 on J3 is shorted.
 *                    BM1383GLV is connected to I2C_2 and does not require interrupt connection.
 *                    BM1422GMV is connected to I2C_3 and INTR5 on J4 is shorted.
 *                    
 */

// include the library
#include <RohmMultiSensor.h>

// instantiate all the sensors' classes
// KX022-1020 uses interrupt 0, BM1422GMV uses interrupt 1
KX022_1020 sensorAcc(INT_0);
BM1383GLV sensorPress;
BM1422GMV sensorMag(INT_1);

// define the interrupt service routine for KX022-1020
void acc_isr(void) {
  sensorAcc.setFlagDrdy();
}

// define the interrupt service routine for BM1422GMV
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

  // initialize all the sensor with default settings
  sensorAcc.init(acc_isr);
  sensorPress.init();
  sensorMag.init(mag_isr);

  Serial.println("X[g]\tY[g]\tZ[g]\tp[hPa]\tX[uT]\tY[uT]\tZ[uT]");
}

void loop() {
  // measure all the sensor values
  sensorAcc.measure();
  sensorPress.measure();
  sensorMag.measure();

  // print the values to the serial port
  Serial.print(sensorAcc.accelX);
  Serial.print('\t');
  Serial.print(sensorAcc.accelY);
  Serial.print('\t');
  Serial.print(sensorAcc.accelZ);
  Serial.print('\t');
  Serial.print(sensorPress.pres);
  Serial.print('\t');
  Serial.print(sensorMag.magX);
  Serial.print('\t');
  Serial.print(sensorMag.magY);
  Serial.print('\t');
  Serial.println(sensorMag.magZ);

  // wait 100 ms before the next measurement
  delay(100);
}
