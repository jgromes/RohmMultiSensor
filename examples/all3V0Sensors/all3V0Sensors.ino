/*
 * All 3.0 V sensors example
 * 
 * This sketch shows you how to use all 3.0 V ROHM sensors simultaneously.
 * 
 * Before powering up your Arduino, make sure to select 3V on jumper J15 on the shield!
 */

// define all the sensors we will use
#define INCLUDE_KX022_1020
#define INCLUDE_BM1383GLV
#define INCLUDE_RPR_0521RS
#define INCLUDE_BH1745NUC
#define INCLUDE_BD1020HFV
#define INCLUDE_ML8511A

// include the library
#include <RohmMultiSensor.h>

//instantiate all the sensors' classes
KX022_1020 acc;
BM1383GLV bar;
RPR_0521RS als;
BH1745NUC rgbc;
BD1020HFV temp;
ML8511A uv;

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
  als.init();
  rgbc.init();
  // temperature sensor (BD1020HFV) is connected to ANALOG_1 header on the shield
  temp.init(ANALOG_1);
  // temperature sensor (ML8511A) is connected to ANALOG_2 header on the shield
  uv.init(ANALOG_2);

  Serial.println("X[g]\tY[g]\tZ[g]\tp[hPa]\tPS[cnt]\tALS[lx]\tR[-]\tG[-]\tB[-]\tC[-]\tt[deg C]\tUV[mW/cm^2]");
}

void loop() {
  // measure all the sensor values
  float* accelValue = acc.measure();
  float pressValue = bar.measure();
  float psValue = als.measure(PS);
  float alsValue = als.measure(ALS);
  unsigned int* rgbcValue = rgbc.measure();
  float tempValue = temp.measure();
  float uvValue = uv.measure();

  // print the values to the serial port
  Serial.print(accelValue[0]);
  Serial.print('\t');
  Serial.print(accelValue[1]);
  Serial.print('\t');
  Serial.print(accelValue[2]);
  Serial.print('\t');
  Serial.print(pressValue);
  Serial.print('\t');
  Serial.print(psValue);
  Serial.print('\t');
  Serial.print(alsValue);
  Serial.print('\t');
  Serial.print(rgbcValue[0]);
  Serial.print('\t');
  Serial.print(rgbcValue[1]);
  Serial.print('\t');
  Serial.print(rgbcValue[2]);
  Serial.print('\t');
  Serial.print(rgbcValue[3]);
  Serial.print('\t');
  Serial.print(tempValue);
  Serial.print('\t');
  Serial.println(uvValue);

  // safely deallocate memory allocated for the dynamic arrays 'accelValue' and 'rgbcValue'
  delete[] accelValue;
  delete[] rgbcValue;

  // wait 100 ms before the next measurement
  delay(100);
}
