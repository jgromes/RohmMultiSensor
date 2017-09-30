#ifndef _ROHM_MULTI_SENSOR_H
  #define _ROHM_MULTI_SENSOR_H

  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif

  #include <Wire.h>
  
  #include "../extras/sensors/Sensor.cpp"

  #ifdef INCLUDE_ALL_SENSORS
    #define INCLUDE_KX022_1020
    #define INCLUDE_BM1383GLV
    #define INCLUDE_BM1422GMV
    #define INCLUDE_RPR_0521RS
    #define INCLUDE_BH1745NUC
    #define INCLUDE_BD7411G
    #define INCLUDE_BD1020HFV
    #define INCLUDE_ML8511A
    #define INCLUDE_BH1790GLC
  #endif
  
  #ifdef INCLUDE_ALL_1V8_SENSORS
    #define INCLUDE_KX022_1020
    #define INCLUDE_BM1383GLV
    #define INCLUDE_BM1422GMV
  #endif
  
  #ifdef INCLUDE_ALL_3V0_SENSORS
    #define INCLUDE_KX022_1020
    #define INCLUDE_BM1383GLV
    #define INCLUDE_RPR_0521RS
    #define INCLUDE_BH1745NUC
    #define INCLUDE_BD1020HFV
    #define INCLUDE_ML8511A
  #endif
  
  #ifdef INCLUDE_ALL_5V0_SENSORS
    #define INCLUDE_BD7411G
    #define INCLUDE_BD1020HFV
  #endif
  
  #ifdef INCLUDE_KX022_1020
    #include "../extras/sensors/KX022_1020.cpp"
  #endif

  #ifdef INCLUDE_BM1383GLV
    #include "../extras/sensors/BM1383GLV.cpp"
  #endif

  #ifdef INCLUDE_BM1422GMV
    #include "../extras/sensors/BM1422GMV.cpp"
  #endif

  #ifdef INCLUDE_RPR_0521RS
    #include "../extras/sensors/RPR_0521RS.cpp"
  #endif

  #ifdef INCLUDE_BH1745NUC
    #include "../extras/sensors/BH1745NUC.cpp"
  #endif

  #ifdef INCLUDE_BD7411G
    #include "../extras/sensors/BD7411G.cpp"
  #endif

  #ifdef INCLUDE_BD1020HFV
    #include "../extras/sensors/BD1020HFV.cpp"
  #endif

  #ifdef INCLUDE_ML8511A
    #include "../extras/sensors/ML8511A.cpp"
  #endif
  
  #ifdef INCLUDE_BH1790GLC
    #include "../extras/sensors/BH1790GLC.cpp"
  #endif
  
#endif
