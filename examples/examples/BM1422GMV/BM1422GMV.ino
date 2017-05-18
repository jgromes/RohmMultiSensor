/*
 * BM1422GMV example
 * 
 * This sketch shows you how to correctly measure magnetic induction using BM1422GMV magnetometer.
 * 
 * Before powering up your Arduino, make sure to select 1.8V on jumper J15 on the shield!
 * 
 * NOTE: The interrupt settings on the shield are following:
 *          J3 jumper connects interrupts to Arduino interrupt 0 (pin D2)
 *          J4 jumper connects interrupts to Arduino interrupt 1 (pin D3)
 *          INTRx pins on J3 and J4 are used to connect CMOS output interrupts for sensors KX022_1020 and BM1422GMV on header I2C_x
 *          INTx pins on J3 and J4 are used to connect interrupts which require external pull-up, these are for sensors BH1745NUC and BM1422GMV on header I2C_x
 *          J16 jumper is ON/OFF switch for the pull-up, when shorted, it will be ON: the pull-up resistor is 1kΩ, the logic HIGH will be 5V.
 *        
 *        If we want to use the BM1422GMV magnetometer, we can connect it to the header I2C_1.
 *        Since BM1422GMV doesn't need an external pull-up, we can directly short INTR1 on J3 if we want to use Arduino interrupt 0 (default setting), or INTR1 on J4 if we want to use Arduino interrupt 1.
 */

// define the sensor we will use
#define INCLUDE_BM1422GMV

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class with the default setting (sensor is using interrupt 0)
BM1422GMV mag;
// the above is equivalent to
// BM1422GMV mag(INT_0);
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
  // note that we have to provide the interrupt service routine to the .init() method
  mag.init(mag_isr);

  Serial.println("X[uT]\tY[uT]\tZ[uT]");
}

void loop() {
  // measure the sensor values
  float* magValue = mag.measure();

  // print the values to the serial port
  Serial.print(magValue[0]);
  Serial.print('\t');
  Serial.print(magValue[1]);
  Serial.print('\t');
  Serial.println(magValue[2]);

  // safely deallocate memory allocated for the dynamic array 'magValue'
  delete[] magValue;

  // wait 100 ms before the next measurement
  delay(100);
}
