/*
 * All 3.0 V sensors example
 * 
 * This sketch shows you how to use all 3.0 V ROHM sensors simultaneously.
 * These sensors are: KX022-1020 accelerometer
 *                    BM1383GLV pressure sensor
 *                    RPR-0521RS proximity/ambient light sensor
 *                    BH1745NUC color sensor
 *                    BD1020HFV temperature sensor
 *                    ML8511A UV sensor
 * 
 * Before powering up your Arduino, make sure to select 3V on jumper J15 on the shield!
 */

// define all the sensors we will use
#define INCLUDE_ALL_3V0_SENSORS

// include the library
#include <RohmMultiSensor.h>

//instantiate all the sensors' classes
KX022_1020 acc;
BM1383GLV bar;
RPR_0521RS als;
BH1745NUC rgbc;
// temperature sensor (BD1020HFV) is connected to ANALOG_1 header on the shield
BD1020HFV temp(ANALOG_1);
// temperature sensor (ML8511A) is connected to ANALOG_2 header on the shield
ML8511A uvr(ANALOG_2);

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize all the sensor with default settings
  acc.init();
  bar.init();
  als.init();
  rgbc.init();
  temp.init();
  uvr.init();

  Serial.println("X[g]\tY[g]\tZ[g]\tp[hPa]\tPS[cnt]\tALS[lx]\tR[-]\tG[-]\tB[-]\tC[-]\tt[dg C]\tUV[mW/cm^2]");
}

void loop() {
  // measure all the sensor values
  acc.measure();
  bar.measure();
  als.measure();
  rgbc.measure();
  temp.measure();
  uvr.measure();

  // print the values to the serial port
  Serial.print(acc.x);
  Serial.print('\t');
  Serial.print(acc.y);
  Serial.print('\t');
  Serial.print(acc.z);
  Serial.print('\t');
  Serial.print(bar.p);
  Serial.print('\t');
  Serial.print(als.ps);
  Serial.print('\t');
  Serial.print(als.als);
  Serial.print('\t');
  Serial.print(rgbc.r);
  Serial.print('\t');
  Serial.print(rgbc.g);
  Serial.print('\t');
  Serial.print(rgbc.b);
  Serial.print('\t');
  Serial.print(rgbc.c);
  Serial.print('\t');
  Serial.print(temp.t);
  Serial.print('\t');
  Serial.println(uvr.uv);

  // wait 100 ms before the next measurement
  delay(100);
}
