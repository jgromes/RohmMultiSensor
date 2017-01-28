# RohmMultiSensor

## Alternative Arduino library for ROHM Sensor Evaluation Kit

DISCLAIMER: This library is provided 'AS IS'. See `license.txt` for details.

This library is an alternative for the libraries provided by ROHM. See [ROHM webpage](http://www.rohm.com/web/global/sensor-shield-support) for details on the ROHM Sensor Evaluation Kit.

This library is compliant with Arduino IDE 1.5 specification.

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

Every sensor's class has to be instantiated beofre use. The class name is the same as the sensor name used in the list of the supported sensors. In the example above:

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
This (default) initialization should work in most cases, but in case you need to change any of the sensors' settings, please refer to the section [Library reference](#library-reference) on details of how to correctly initialize each of the supported sensors.

After all the sensor have been succefully initialized, you can access their data by calling `.measure()` method.
Please note that the return data types vary for each of the sensors, for details on all of them, please refer to the section [Library reference](#library-reference).

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

    `uint8_t address = KX022_1020_DEVICE_ADDRESS_L` Default value, the default I2C address.  
    `uint8_t address = KX022_1020_DEVICE_ADDRESS_H` The sensor I2C adress in case the pin ADDR is set to HIGH.
    
  * `int KX022_1020::init(uint8_t range, uint8_t rate)` The initialization function.
  
    `uint8_t range = KX022_1020_RANGE_4G` Default value, output is in range +-4g.  
    `uint8_t range = KX022_1020_RANGE_2G` Output is in range +-2g.  
    `uint8_t range = KX022_1020_RANGE_8G` Output is in range +-8g.  
    `uint8_t rate = KX022_1020_OUTPUT_RATE_50_HZ` Default value, data output rate is 50 Hz.  
    `uint8_t rate = KX022_1020_OUTPUT_RATE_<n>_HZ` Other possible data output rates in Hz, see `/sensors/KX022_1020.cpp` for details.
    
  * `float* KX022_1020::measure(void)` The measurement function.
  
    The output data type is a pointer to an array of 3 `float` numbers. The first element is the X axis, second is the Y axis and third is the Z axis. The output value is in g.  
    IMPORTANT: The array is allocated dynamically, and therefore has to be deleted with `delete[]` after usage. This is to prevent memory leak.

* BM1383GLV
  * `BM1383GLV::BM1383GLV(uint8_t address)` The default constructor.
  
    `uint8_t address = BM1383GLV_DEVICE_ADDRESS` Default value, the default I2C address.
    
  * `int BM1383GLV::init(uint8_t mode, uint8_t avg, uint8_t tempAvg)` The initialization function.
  
    `uint8_t mode = BM1383GLV_CONTINUOUS_200_MS` Default value, continuous measurement mode over 200 ms.  
    `uint8_t mode = BM1383GLV_<mode_name>` Other possible measurement modes, see `/sensors/BM1383GLV.cpp` for details.  
    `uint8_t avg = BM1383GLV_AVERAGE_64` Default value, the output value will be an average of 64 measurements.  
    `uint8_t avg = BM1383GLV_AVERAGE_<n>` Other possible averaging values, see `/sensors/BM1383GLV.cpp` for details.
    
  * `float BM1383GLV::measure(void)` The measurement function.
  
    The output data type is a single `float` number. The output value is in hPa.

* BM1422GMV
  * `BM1422GMV::BM1422GMV(uint8_t intNum, uint8_t address)` The default constructor.
  
    `uint8_t address = BM1422GMV_DEVICE_ADDRESS_L` Default value, the default I2C address.  
    `uint8_t address = BM1422GMV_DEVICE_ADDRESS_H` The sensor I2C adress in case the pin ADDR is set to HIGH.  
    `uint8_t intNum = INT_0` Default value, the connected Arduino interrupt is interrupt 0. Note that this is NOT the Arduino pin number!  
    `uint8_t intNum = INT_1` The connected Arduino interrupt is interrupt 1. Note that this is NOT the Arduino pin number!
    
  * `int BM1422GMV::init(void func(void), uint8_t mode, uint8_t rate, uint8_t output, uint8_t avg)` The initialization function.
  
    `void func(void)` The interrupt service routine, see `examples/BM1422GMV` for details.  
    `uint8_t mode = BM1422GMV_MODE_SINGLE` Default value, single measurement mode.  
    `uint8_t mode = BM1422GMV_MODE_CONTINUOUS` Continuous measurement mode.  
    `uint8_t rate = BM1422GMV_OUTPUT_RATE_10_HZ` Default value, data output rate is 10 Hz.  
    `uint8_t rate = BM1422GMV_OUTPUT_RATE_<n>` Other possible data output rates in Hz, see `/sensors/BM1422GMV.cpp` for details.  
    `uint8_t output = BM1422GMV_OUTPUT_14_BIT` Default value. Ouput will be 14-bit number.  
    `uint8_t output = BM1422GMV_OUTPUT_12_BIT` Ouput will be 12-bit number.  
    `uint8_t avg = BM1422GMV_AVERAGE_4` Default value, the output value will be an average of 4 measurements.  
    `uint8_t avg = BM1422GMV_AVERAGE_<n>` Other possible averaging values, see `/sensors/BM1422GMV.cpp` for details.
    
  * `float* BM1422GMV::measure(void)` The measurement function.
  
    The output data type is a pointer to an array of 3 `float` numbers. The first element is the X axis, second is the Y axis and third is the Z axis. The output value is in uT.  
    IMPORTANT: The array is allocated dynamically, and therefore has to be deleted with `delete[]` after usage. This is to prevent memory leak.

* RPR_0521RS
  * `RPR_0521RS::RPR_0521RS(uint8_t address)` The default constructor.
  
    `uint8_t address = RPR_0521RS_DEVICE_ADDRESS` Default value, the default I2C address.
    
  * `int RPR_0521RS::init(uint8_t measurementTime, uint8_t ledCurrent)` The initialization function.
  
    `uint8_t measurementTime = RPR_0521RS_MEAS_TIME_100_MS_100_MS` Default value, ambient light sensor (ALS) measurement time is 100 ms, proximity sensor (PS) measurement time is 100 ms.  
    `uint8_t measurementTime = RPR_0521RS_MEAS_TIME_<als_time>_<ps_time>` Other possible measurement time values, see `/sensors/RPR_0521RS.cpp` for details.  
    `uint8_t ledCurrent = RPR_0521RS_LED_CURRENT_100_MA` Default value, LED current is 100 mA.  
    `uint8_t ledCurrent = RPR_0521RS_LED_CURRENT_<n>_MA` Other possible LED current values, see `/sensors/RPR_0521RS.cpp` for details.
    
  * `float RPR_0521RS::measure(uint8_t type)` The measurement function.
  
    `uint8_t type = ALS` Default value. The sensor will measure ambient light level in lux.  
    `uint8_t type = PS` The sensor will measure proximity in number of ticks, the closer the object is, the higher will be the output.
    
    The output data type is a single `float` number.

* BH1745NUC
  * `BH1745NUC::BH1745NUC(uint8_t address)` The default constructor.
  
    `uint8_t address = BH1745NUC_DEVICE_ADDRESS_H` Default value, the default I2C address.  
    `uint8_t address = BM1422GMV_DEVICE_ADDRESS_L` The sensor I2C adress in case the pin ADDR is set to LOW.
    
  * `int BH1745NUC::init(uint8_t measurementTime)` The initialization function.  
    `uint8_t measurementTime = BH1745NUC_MEAS_TIME_160_MS` Default value, measurement time is 160 ms.  
    `uint8_t measurementTime = BM1422GMV_MEAS_TIME_<n>_MS` Other possible measurement times in ms, see `/sensors/BH1745NUC.cpp` for details.
    
  * `uint16_t* BM1422GMV::measure(void)` The measurement function.
  
    The output data type is a pointer to an array of 4 `uint16_t` numbers. The first element is the RED value, second is the GREEN value, third is BLUE value and fourth is CLEAR value.  
    IMPORTANT: The array is allocated dynamically, and therefore has to be deleted with `delete[]` after usage. This is to prevent memory leak.

* BD7411G
  * `BD7411G::BD7411G(void)` The default constructor.
  
  * `int BD7411G::init(uint8_t pin = 0)` The initialization function.
  
    `uint8_t pin = 0` Default value, this is the Arduino digital pin the GPIO header on the shield is connected to (D0).
    
  * `bool BD7411G::measure(void)` The measurement function.
  
    The output data type is a single `bool` numbers. The output is true if a magnetic field is detected and false if it is not.

* BD1020HFV
  * `BD1020HFV::BD1020HFV(void)` The default constructor.
  
  * `int BD1020HFV::init(uint8_t position = ANALOG_1)` The initialization function.
  
    `uint8_t position = ANALOG_1` Default value, in case the sensor is connected to ANALOG_1 pin header on the shield.  
    `uint8_t position = ANALOG_2` In case the sensor is connected to ANALOG_2 pin header on the shield.
    
  * `float BD1020HFV::measure(void)` The measurement function.
  
    The output data type is a single `float` numbers. The output is in degrees Celsius.

* ML8511A
  * `ML8511A::ML8511A(void)` The default constructor.
  
  * `int ML8511A::init(uint8_t position = ANALOG_1)` The initialization function.
  
    `uint8_t position = ANALOG_1` Default value, in case the sensor is connected to ANALOG_1 pin header on the shield.  
    `uint8_t position = ANALOG_2` In case the sensor is connected to ANALOG_2 pin header on the shield.
    
  * `float ML8511A::measure(void)` The measurement function.
  
    The output data type is a single `float` numbers. The output is in mW/cm^2.
