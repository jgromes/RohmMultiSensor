#ifndef _ROHM_MULTI_SENSOR_H
  #define _ROHM_MULTI_SENSOR_H

  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif

  #include <Wire.h>
  
  #include "../sensors/utilities.cpp"

  #ifdef INCLUDE_KX022_1020
    #include "../sensors/KX022_1020.cpp"
  #endif

  #ifdef INCLUDE_BM1383GLV
    #include "../sensors/BM1383GLV.cpp"
  #endif

  #ifdef INCLUDE_BM1422GMV
    #include "../sensors/BM1422GMV.cpp"
  #endif

  #ifdef INCLUDE_RPR_0521RS
    #include "../sensors/RPR_0521RS.cpp"
  #endif

  #ifdef INCLUDE_BH1745NUC
    #include "../sensors/BH1745NUC.cpp"
  #endif

  #ifdef INCLUDE_BD7411G
    #include "../sensors/BD7411G.cpp"
  #endif

  #ifdef INCLUDE_BD1020HFV
    #include "../sensors/BD1020HFV.cpp"
  #endif

  #ifdef INCLUDE_ML8511A
    #include "../sensors/ML8511A.cpp"
  #endif

#endif
