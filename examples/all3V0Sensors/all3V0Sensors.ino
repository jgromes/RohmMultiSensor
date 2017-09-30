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
KX022_1020 sensorAcc;
BM1383GLV sensorPress;
RPR_0521RS sensorAls;
BH1745NUC sensorColor;
// temperature sensor (BD1020HFV) is connected to ANALOG_1 header on the shield
BD1020HFV sensorTmp(ANALOG_1);
// temperature sensor (ML8511A) is connected to ANALOG_2 header on the shield
ML8511A sensorUV(ANALOG_2);

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize all the sensor with default settings
  sensorAcc.init();
  sensorPress.init();
  sensorAls.init();
  sensorColor.init();
  sensorTmp.init();
  sensorUV.init();

  Serial.println("X[g]\tY[g]\tZ[g]\tp[hPa]\tPS[cnt]\tALS[lx]\tR[-]\tG[-]\tB[-]\tC[-]\tt[dg C]\tUV[mW/cm^2]");
}

void loop() {
  // measure all the sensor values
  sensorAcc.measure();
  sensorPress.measure();
  sensorAls.measure();
  sensorColor.measure();
  sensorTmp.measure();
  sensorUV.measure();

  // print the values to the serial port
  Serial.print(sensorAcc.accelX);
  Serial.print('\t');
  Serial.print(sensorAcc.accelY);
  Serial.print('\t');
  Serial.print(sensorAcc.accelZ);
  Serial.print('\t');
  Serial.print(sensorPress.pres);
  Serial.print('\t');
  Serial.print(sensorAls.prox);
  Serial.print('\t');
  Serial.print(sensorAls.ambLight);
  Serial.print('\t');
  Serial.print(sensorColor.red);
  Serial.print('\t');
  Serial.print(sensorColor.green);
  Serial.print('\t');
  Serial.print(sensorColor.blue);
  Serial.print('\t');
  Serial.print(sensorColor.clear);
  Serial.print('\t');
  Serial.print(sensorTmp.temp);
  Serial.print('\t');
  Serial.println(sensorUV.uvRad);

  // wait 100 ms before the next measurement
  delay(100);
}
