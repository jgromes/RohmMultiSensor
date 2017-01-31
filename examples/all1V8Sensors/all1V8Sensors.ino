/*
 * All 1.8 V sensors example
 * 
 * This sketch shows you how to use all 1.8 V ROHM sensors simultaneously.
 * 
 * Before powering up your Arduino, make sure to select 1.8V on jumper J15 on the shield!
 */

// define all the sensors we will use
#define INCLUDE_ALL_1V8_SENSORS

// include the library
#include <RohmMultiSensor.h>

//instantiate all the sensors' classes
KX022_1020 acc;
BM1383GLV bar;
BM1422GMV mag;

// define the interrupt service routine for BM1422GMV
void isr(void) {
  mag.setFlagDrdy();
}


void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize all the sensor with default values.
  acc.init();
  bar.init();
  mag.init(*isr);

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
