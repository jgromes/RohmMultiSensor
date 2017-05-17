/*
 * KX022_1020 example
 * 
 * This sketch shows you how to correctly setup iterrupts to use KX022-1020 accelerometer.
 * 
 * Before powering up your Arduino, make sure to select 1.8V or 3V on jumper J15 on the shield!
 * 
 * NOTE: The interrupt settings on the shield are following:
 *          J3 jumper connects interrupts to Arduino interrupt 0 (pin D2)
 *          J4 jumper connects interrupts to Arduino interrupt 1 (pin D3)
 *          INTRx pins on J3 and J4 are used to connect CMOS output interrupts for sensors KX022_1020 and BM1422GMV on header I2C_x
 *          INTx pins on J3 and J4 are used to connect interrupts which require external pull-up, these are for sensors BH1745NUC and BM1422GMV on header I2C_x
 *          J16 jumper is ON/OFF switch for the pull-up, when shorted, it will be ON: the pull-up resistor is 1kΩ, the logic HIGH will be 5V.
 *        
 *        If we want to use the KX022-1020 accelerometer, we can connect it to the header I2C_1.
 *        Since KX022-1020 doesn't need an external pull-up, we can directly short INTR1 on J3 if we want to use Arduino interrupt 0 (default setting), or INTR1 on J4 if we want to use Arduino interrupt 1.
 */

// define all the sensors we will use
#define INCLUDE_KX022_1020

// include the library
#include <RohmMultiSensor.h>

// instantiate the sensor's class
KX022_1020 acc;

// define the interrupt service routine
void isr(void) {
  acc.setFlagDrdy();
}

void setup() {
  // begin serial communication
  Serial.begin(9600);
  Serial.println();

  // begin the TWI (I2C) interface.
  // this function has to be called before any calls to .init()!
  Wire.begin();

  // initialize KX022-1020 with the default values
  // note that we have to provide the interrupt service routine to the .init() method
  acc.init(isr);

  Serial.println("X[g]\tY[g]\tZ[g]");
}

void loop() {
  // measure the sensor values
  float* accelValue = acc.measure();

  // print the values to the serial port
  Serial.print(accelValue[0]);
  Serial.print('\t');
  Serial.print(accelValue[1]);
  Serial.print('\t');
  Serial.println(accelValue[2]);

  // safely deallocate memory allocated for the dynamic array 'accelValue'
  delete[] accelValue;

  // wait 100 ms before the next measurement
  delay(100);
}
