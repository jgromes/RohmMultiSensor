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
 *                    BM1422GMV is connected to I2C_2 and INTR4 on J4 is shorted.
 *                    BM1383GLV does not require interrupt connection.
 *                    See library reference for details.
 */

// define all the sensors we will use
#define INCLUDE_ALL_1V8_SENSORS

// include the library
#include <RohmMultiSensor.h>

// instantiate all the sensors' classes
// KX022-1020 uses interrupt 0, BM1422GMV uses interrupt 1
KX022_1020 acc(INT_0);
BM1383GLV bar;
BM1422GMV mag(INT_1);

// define the interrupt service routine for KX022-1020
void acc_isr(void) {
  acc.setFlagDrdy();
}

// define the interrupt service routine for BM1422GMV
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

  // initialize all the sensor with default settings
  acc.init(acc_isr);
  bar.init();
  mag.init(mag_isr);

  Serial.println("X[g]\tY[g]\tZ[g]\tp[hPa]\tX[uT]\tY[uT]\tZ[uT]");
}

void loop() {
  // measure all the sensor values
  float* accelValue = acc.measure();
  float pressValue = bar.measure();
  float* magValue = mag.measure();

  // print the values to the serial port
  Serial.print(accelValue[0]);
  Serial.print('\t');
  Serial.print(accelValue[1]);
  Serial.print('\t');
  Serial.print(accelValue[2]);
  Serial.print('\t');
  Serial.print(pressValue);
  Serial.print('\t');
  Serial.print(magValue[0]);
  Serial.print('\t');
  Serial.print(magValue[1]);
  Serial.print('\t');
  Serial.println(magValue[2]);

  // safely deallocate memory allocated for the dynamic arrays 'accelValue' and 'magValue'
  delete[] accelValue;
  delete[] magValue;

  // wait 100 ms before the next measurement
  delay(100);
}
