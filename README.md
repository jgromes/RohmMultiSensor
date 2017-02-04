# RohmMultiSensor

## Alternative Arduino library for ROHM Sensor Evaluation Kit

DISCLAIMER: This library is provided 'AS IS'. See `license.txt` for details.

This library is an alternative to the libraries provided by ROHM. See [ROHM webpage](http://www.rohm.com/web/global/sensor-shield-support) for details on the ROHM Sensor Evaluation Kit.

Main purpose of this library is to allow easier, more lightweight interfacing with ROHM sensors.

When using all currently supported sensors with RohmMultiSensor and a simple serial output, the sketch after compilation (for Arduino UNO) uses 20% less program storage space and 30% less dynamic memory that the libraries provided by ROHM need!

Furthemore, RohmMultiSensor is a single library, as opposed to ROHM-provided one-library-per-sensor.

Finally, this library is compliant with Arduino IDE 1.5 specification.

## Basic usage
The following is a list of currently supported sensors:

* KX022_1020
* BM1383GLV
* BM1422GMV
* RPR_0521RS
* BH1745NUC
* BD7411G
* BD1020HFV
* ML8511A
* BH1790GLC

For any sensor that will be used in the Arduino sketch, the following has to be defined BEFORE the library header file inclusion. The `<sensor_name>` is the same as in the list above.

```c++
#define INCLUDE_<sensor_name>
//possible another sensor definitions

#include <RohmMultiSensor.h>
```

For example, if you want to interface with KX022-1020 accelerometer and BM1383 pressure sensor, your Arduino sketch will begin like this:

```c++
#define INCLUDE_KX022_1020
#define INCLUDE_BM1383GLV

#include <RohmMultiSensor.h>
```

IMPORTANT: You will not be able to use any sensors for which you have not provided the `#define`! This is to ensure that only the required sensors are included, reducing overall program size.

Alternatively, you can `#define` all the sensors that shaer the same supply voltage. In this example, we will include all sensors that run on 1.8 V:

```c++
#define INCLUDE_ALL_1V8_SENSORS

#include <RohmMultiSensor.h>
```

Other possibilities are: `INCLUDE_ALL_3V0_SENSORS` or `INCLUDE_ALL_5V0_SENSORS` for 3 V or 5 V sensors.

Every sensor's class has to be instantiated before use. The class name is the same as the sensor name used in the list of the supported sensors. If we continue with the example:

```c++
#define INCLUDE_KX022_1020
#define INCLUDE_BM1383GLV

#include <RohmMultiSensor.h>

KX022_1020 acc;
BM1383 bar;
```

After the instantization, in the Arduino `setup()` function, each sensor has to be initialized. This is done by calling `.init()` method for each of the sensors.
Also, since some of the sensors use I2C (aka TWI) interface, be sure to add `Wire.begin()` BEFORE the `.init()` initialization!

```c++
#define INCLUDE_KX022_1020
#define INCLUDE_BM1383GLV

#include <RohmMultiSensor.h>

KX022_1020 acc;
BM1383 bar;

void setup() {
  Wire.begin();
  
  acc.init();
  bar.init();
}
```

The `.init()` method returns -1 in case the sensor initialization fails, this can be used to catch any errors that may occur.
This (default) initialization should work in most cases, but in case you need to change any of the sensors' settings, please refer to the [Library reference](#library-reference) on details of how to correctly initialize each of the supported sensors.

After all the sensor have been succefully initialized, you can access their data by calling `.measure()` method.
Please note that the return data types vary for each of the sensors, for details on all of them, please refer to the [Library reference](#library-reference).

```c++
#define INCLUDE_KX022_1020
#define INCLUDE_BM1383GLV

#include <RohmMultiSensor.h>

KX022_1020 acc;
BM1383 bar;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  acc.init();
  bar.init();
}

void loop() {
  float* accelValue = acc.measure();
  float pressValue = bar.measure();
  
  //use the values measured above here
  Serial.println(accelValue[0]);
  Serial.println(accelValue[1]);
  Serial.println(accelValue[2]);
  Serial.println(pressValue);
  
  delete[] accelValue;
  delay(100);
}
```

## Library reference
* KX022_1020
  * `KX022_1020::KX022_1020(uint8_t address)` The default constructor.

    `address = KX022_1020_DEVICE_ADDRESS_L` Default value, the default I2C address.  
    `address = KX022_1020_DEVICE_ADDRESS_H` The sensor I2C adress in case the pin ADDR is set to HIGH.
    
  * `int KX022_1020::init(uint8_t range, uint8_t rate)` The initialization function.
  
    `range = KX022_1020_RANGE_4G` Default value, output is in range +-4g.  
    `range = KX022_1020_RANGE_2G` Output is in range +-2g.  
    `range = KX022_1020_RANGE_8G` Output is in range +-8g.  
    `rate = KX022_1020_OUTPUT_RATE_50_HZ` Default value, data output rate is 50 Hz.  
    `rate = KX022_1020_OUTPUT_RATE_<n>_HZ` Other possible data output rates in Hz, see `/sensors/KX022_1020.cpp` for details.
    
  * `float* KX022_1020::measure(void)` The measurement function.
  
    The output data type is a pointer to an array of 3 `float` numbers. The first element is the X axis, second is the Y axis and third is the Z axis. The output value is in g.  
    IMPORTANT: The array is allocated dynamically, and therefore has to be deleted with `delete[]` after usage. This is to prevent memory leak.

* BM1383GLV
  * `BM1383GLV::BM1383GLV(uint8_t address)` The default constructor.
  
    `address = BM1383GLV_DEVICE_ADDRESS` Default value, the default I2C address.
    
  * `int BM1383GLV::init(uint8_t mode, uint8_t avg, uint8_t tempAvg)` The initialization function.
  
    `mode = BM1383GLV_CONTINUOUS_200_MS` Default value, continuous measurement mode over 200 ms.  
    `mode = BM1383GLV_<mode_name>` Other possible measurement modes, see `/sensors/BM1383GLV.cpp` for details.  
    `avg = BM1383GLV_AVERAGE_64` Default value, the output value will be an average of 64 measurements.  
    `avg = BM1383GLV_AVERAGE_<n>` Other possible averaging values, see `/sensors/BM1383GLV.cpp` for details.
    
  * `float BM1383GLV::measure(void)` The measurement function.
  
    The output data type is a single `float` number. The output value is in hPa.

* BM1422GMV
  * `BM1422GMV::BM1422GMV(uint8_t intNum, uint8_t address)` The default constructor.
  
    `address = BM1422GMV_DEVICE_ADDRESS_L` Default value, the default I2C address.  
    `address = BM1422GMV_DEVICE_ADDRESS_H` The sensor I2C adress in case the pin ADDR is set to HIGH.  
    `intNum = INT_0` Default value, the connected Arduino interrupt is interrupt 0. Note that this is NOT the Arduino pin number!  
    `intNum = INT_1` The connected Arduino interrupt is interrupt 1. Note that this is NOT the Arduino pin number!
    
  * `int BM1422GMV::init(void func(void), uint8_t mode, uint8_t rate, uint8_t output, uint8_t avg)` The initialization function.
  
    `void func(void)` The interrupt service routine, see `/examples/BM1422GMV` and [Notes](#notes) for details on how to use interrupts.  
    `mode = BM1422GMV_MODE_SINGLE` Default value, single measurement mode.  
    `mode = BM1422GMV_MODE_CONTINUOUS` Continuous measurement mode.  
    `rate = BM1422GMV_OUTPUT_RATE_10_HZ` Default value, data output rate is 10 Hz.  
    `rate = BM1422GMV_OUTPUT_RATE_<n>` Other possible data output rates in Hz, see `/sensors/BM1422GMV.cpp` for details.  
    `output = BM1422GMV_OUTPUT_14_BIT` Default value. Ouput will be 14-bit number.  
    `output = BM1422GMV_OUTPUT_12_BIT` Ouput will be 12-bit number.  
    `avg = BM1422GMV_AVERAGE_4` Default value, the output value will be an average of 4 measurements.  
    `avg = BM1422GMV_AVERAGE_<n>` Other possible averaging values, see `/sensors/BM1422GMV.cpp` for details.
    
  * `float* BM1422GMV::measure(void)` The measurement function.
  
    The output data type is a pointer to an array of 3 `float` numbers. The first element is the X axis, second is the Y axis and third is the Z axis. The output value is in uT.  
    IMPORTANT: The array is allocated dynamically, and therefore has to be deleted with `delete[]` after usage. This is to prevent memory leak.

* RPR_0521RS
  * `RPR_0521RS::RPR_0521RS(uint8_t address)` The default constructor.
  
    `address = RPR_0521RS_DEVICE_ADDRESS` Default value, the default I2C address.
    
  * `int RPR_0521RS::init(uint8_t measurementTime, uint8_t ledCurrent)` The initialization function.
  
    `measurementTime = RPR_0521RS_MEAS_TIME_100_MS_100_MS` Default value, ambient light sensor (ALS) measurement time is 100 ms, proximity sensor (PS) measurement time is 100 ms.  
    `measurementTime = RPR_0521RS_MEAS_TIME_<als_time>_<ps_time>` Other possible measurement time values, see `/sensors/RPR_0521RS.cpp` for details.  
    `ledCurrent = RPR_0521RS_LED_CURRENT_100_MA` Default value, LED current is 100 mA.  
    `ledCurrent = RPR_0521RS_LED_CURRENT_<n>_MA` Other possible LED current values, see `/sensors/RPR_0521RS.cpp` for details.
    
  * `float RPR_0521RS::measure(uint8_t type)` The measurement function.
  
    `type = ALS` Default value. The sensor will measure ambient light level in lux.  
    `type = PS` The sensor will measure proximity in number of ticks, the closer the object is, the higher will be the output.
    
    The output data type is a single `float` number.

* BH1745NUC
  * `BH1745NUC::BH1745NUC(uint8_t address)` The default constructor.
  
    `address = BH1745NUC_DEVICE_ADDRESS_H` Default value, the default I2C address.  
    `address = BM1422GMV_DEVICE_ADDRESS_L` The sensor I2C adress in case the pin ADDR is set to LOW.
    
  * `int BH1745NUC::init(uint8_t measurementTime)` The initialization function.
  
    `measurementTime = BH1745NUC_MEAS_TIME_160_MS` Default value, measurement time is 160 ms.  
    `measurementTime = BM1422GMV_MEAS_TIME_<n>_MS` Other possible measurement times in ms, see `/sensors/BH1745NUC.cpp` for details.
    
  * `uint16_t* BM1422GMV::measure(void)` The measurement function.
  
    The output data type is a pointer to an array of 4 `uint16_t` numbers. The first element is the RED value, second is the GREEN value, third is BLUE value and fourth is CLEAR value.  
    IMPORTANT: The array is allocated dynamically, and therefore has to be deleted with `delete[]` after usage. This is to prevent memory leak.

* BD7411G
  * `BD7411G::BD7411G(void)` The default constructor.
  
  * `int BD7411G::init(uint8_t pin = 0)` The initialization function.
  
    `pin = 0` Default value, this is the Arduino digital pin the GPIO header on the shield is connected to (D0).
    
  * `bool BD7411G::measure(void)` The measurement function.
  
    The output data type is a single `bool` numbers. The output is true if a magnetic field is detected and false if it is not.

* BD1020HFV
  * `BD1020HFV::BD1020HFV(void)` The default constructor.
  
  * `int BD1020HFV::init(uint8_t position = ANALOG_1)` The initialization function.
  
    `position = ANALOG_1` Default value, in case the sensor is connected to ANALOG_1 pin header on the shield.  
    `position = ANALOG_2` In case the sensor is connected to ANALOG_2 pin header on the shield.
    
  * `float BD1020HFV::measure(void)` The measurement function.
  
    The output data type is a single `float` numbers. The output is in degrees Celsius.

* ML8511A
  * `ML8511A::ML8511A(void)` The default constructor.
  
  * `int ML8511A::init(uint8_t position)` The initialization function.
  
    `position = ANALOG_1` Default value, in case the sensor is connected to ANALOG_1 pin header on the shield.  
    `position = ANALOG_2` In case the sensor is connected to ANALOG_2 pin header on the shield.
    
  * `float ML8511A::measure(void)` The measurement function.
  
    The output data type is a single `float` numbers. The output is in mW/cm^2.

* BH1790GLC
  * `BH1790GLC::BH1790GLC(uint8_t address)` The default constructor.
  
    `address = BH1790GLC_DEVICE_ADDRESS` Default value, the default I2C address.
  
  * `int BH1790GLC::init(uint8_t readCycle, uint8_t ledCurrent)` The initialization function.
  
    `readCycle = BH1790GLC_RCYCLE_32_HZ` Default value, this is the maximum frequency at which you can access the data (32 Hz).  
    `readCycle = BH1790GLC_RCYCLE_64_HZ` 64 Hz data access frequency. See [Notes](#notes) for details.  
    `ledCurrent = BH1790GLC_LED_CURRENT_6_MA` Default value, the current for the LED diodes is 6 mA.  
    `ledCurrent = BH1790GLC_LED_CURRENT_<n>_MA` Other possible values in mA, see `/sensors/BH1790GLC.cpp` for details.
    
  * `int* BH1790GLC::measure(void)` The measurement function.
  
    The output data type is a pointer to an array of 2 `int` numbers. The first element is `LEDON` data, the second is `LEDOFF` data, see datasheet for details.  
    IMPORTANT: The array is allocated dynamically, and therefore has to be deleted with `delete[]` after usage. This is to prevent memory leak.


## Notes
1. When using the BD7411G Hall sensor, be sure to disconnect the sensor from the shield before uploading the sketch!
  Since BD7411G's OUT pin is directly connected to Arduino D0 (serial RX), any attempt to upload with the sensor connected will lead to avrdude: stk500_getsync() error.
  
2. The interrupt settings on the shield are following:  
  * J3 jumper connects interrupts to Arduino interrupt 0 (pin D2)  
  * J4 jumper connects interrupts to Arduino interrupt 1 (pin D3)  
  * INTRx pins on J3 and J4 are used to connect CMOS output interrupts for sensors KX022_1020 and BM1422GMV on header I2C_x  
  * INTx pins on J3 and J4 are used to connect interrupts which require external pull-up, these are for sensors BH1745NUC and RPR-0521RS on header I2C_x  
  * J16 jumper is ON/OFF switch for the pull-up, when shorted, it will be ON: the pull-up resistor is 1kΩ, the logic HIGH will be 5V.
  
  Example: If we want to use the BM1422GMV magnetometer, we can connect it to the header I2C_1. Since BM1422GMV doesn't need an external pull-up, we can directly short INTR1 on J3 if we want to use Arduino interrupt 0 (default setting), or INTR1 on J4 if we want to use Arduino interrupt 1. See `/examples/BM1422GMV` for details.

3. When using the BH1790GLC, make sure that you are not trying to read the data faster than the `readCycle` frequency. For example, if you leave the default value, you have to wait at least 1/32 seconds before accessing the sensor again.
