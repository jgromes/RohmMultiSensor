#ifndef _KX022_1020_CPP
#define _KX022_1020_CPP

//KX022-1020 register map
#define KX022_1020_REG_XHPL                           0x00
#define KX022_1020_REG_XHPH                           0x01
#define KX022_1020_REG_YHPL                           0x02
#define KX022_1020_REG_YHPH                           0x03
#define KX022_1020_REG_ZHPL                           0x04
#define KX022_1020_REG_ZHPH                           0x05
#define KX022_1020_REG_XOUTL                          0x06
#define KX022_1020_REG_XOUTH                          0x07
#define KX022_1020_REG_YOUTL                          0x08
#define KX022_1020_REG_YOUTH                          0x09
#define KX022_1020_REG_ZOUTL                          0x0A
#define KX022_1020_REG_ZOUTH                          0x0B
#define KX022_1020_REG_COTR                           0x0C
#define KX022_1020_REG_WHO_AM_I                       0x0F
#define KX022_1020_REG_TSCP                           0x10
#define KX022_1020_REG_TSPP                           0x11
#define KX022_1020_REG_INS1                           0x12
#define KX022_1020_REG_INS2                           0x13
#define KX022_1020_REG_INS3                           0x14
#define KX022_1020_REG_STAT                           0x15
#define KX022_1020_REG_INT_REL                        0x17
#define KX022_1020_REG_CNTL1                          0x18
#define KX022_1020_REG_CNTL2                          0x19
#define KX022_1020_REG_CNTL3                          0x1A
#define KX022_1020_REG_ODCNTL                         0x1B
#define KX022_1020_REG_INC1                           0x1C
#define KX022_1020_REG_INC2                           0x1D
#define KX022_1020_REG_INC3                           0x1E
#define KX022_1020_REG_INC4                           0x1F
#define KX022_1020_REG_INC5                           0x20
#define KX022_1020_REG_INC6                           0x21
#define KX022_1020_REG_TILT_TIMER                     0x22
#define KX022_1020_REG_WUFC                           0x23
#define KX022_1020_REG_TDTRC                          0x24
#define KX022_1020_REG_TDTC                           0x25
#define KX022_1020_REG_TTH                            0x26
#define KX022_1020_REG_TTL                            0x27
#define KX022_1020_REG_FTD                            0x28
#define KX022_1020_REG_STD                            0x29
#define KX022_1020_REG_TLT                            0x2A
#define KX022_1020_REG_TWS                            0x2B
#define KX022_1020_REG_ATH                            0x30
#define KX022_1020_REG_TILT_ANGLE_LL                  0x32
#define KX022_1020_REG_TILT_ANGLE_HL                  0x33
#define KX022_1020_REG_HYST_SET                       0x34
#define KX022_1020_REG_LP_CNTL                        0x35
#define KX022_1020_REG_BUF_CNTL1                      0x3A
#define KX022_1020_REG_BUF_CNTL2                      0x3B
#define KX022_1020_REG_BUF_STATUS_1                   0x3C
#define KX022_1020_REG_BUF_STATUS_2                   0x3D
#define KX022_1020_REG_BUF_CLEAR                      0x3E
#define KX022_1020_REG_BUF_READ                       0x3F
#define KX022_1020_REG_SELF_TEST                      0x60

//KX022-1020 default values
#define KX022_1020_DEVICE_ADDRESS_L                   0x1E
#define KX022_1020_DEVICE_ADDRESS_H                   0x1F
#define KX022_1020_WHO_AM_I                           0x14
#define INT_0                                         0x00
#define INT_1                                         0x01
#define INT_NONE                                      0xFF

//KX022-1020 settings
//KX022_1020_REG_CNTL1                                                MSB   LSB   DESCRIPTION
#define KX022_1020_STANDBY                            0b00000000  //  7     7     allows to change settings
#define KX022_1020_OPERATE                            0b10000000  //  7     7     start measuring; needs 1.2/KX022_1020_OUTPUT_RATE_n delay to load settings
#define KX022_1020_LOW_POWER                          0b00000000  //  6     6     low current draw, lower resolution
#define KX022_1020_HIGH_RESOLUTION                    0b01000000  //  6     6     high resolution, higher current draw
#define KX022_1020_DATA_READY_OFF                     0b00000000  //  5     5     disable new data interrupt
#define KX022_1020_DATA_READY_ON                      0b00100000  //  5     5     enable new data interrupt
#define KX022_1020_RANGE_2G                           0b00000000  //  4     3     set the output range to +-2g
#define KX022_1020_RANGE_4G                           0b00001000  //  4     3     set the output range to +-4g
#define KX022_1020_RANGE_8G                           0b00011000  //  4     3     set the output range to +-8g
#define KX022_1020_TAP_DETECT_OFF                     0b00000000  //  2     2     disable Directional Tap (TM) function
#define KX022_1020_TAP_DETECT_ON                      0b00000100  //  2     2     enable Directional Tap (TM) function
#define KX022_1020_WAKE_UP_OFF                        0b00000000  //  1     1     disable wake up on motion detect
#define KX022_1020_WAKE_UP_ON                         0b00000010  //  1     1     enable wake up on motion detect
#define KX022_1020_TILT_POSITION_OFF                  0b00000000  //  0     0     disable detection of orientation changes
#define KX022_1020_TILT_POSITION_ON                   0b00000001  //  0     0     enable detection of orientation changes
//KX022_1020_REG_ODCNTL
#define KX022_1020_IIR_BYPASS_OFF                     0b00000000  //  7     7     filtering applied
#define KX022_1020_IIR_BYPASS_ON                      0b10000000  //  7     7     filtering bypassed
#define KX022_1020_LOW_PASS_FILTER_ODR_9              0b00000000  //  6     6     low pass filter corner frequency: KX022_1020_OUTPUT_RATE_n/9
#define KX022_1020_LOW_PASS_FILTER_ODR_2              0b01000000  //  6     6                                       KX022_1020_OUTPUT_RATE_n/2
#define KX022_1020_OUTPUT_RATE_12_5_HZ                0b00000000  //  3     0     data output rate: 12.5 Hz
#define KX022_1020_OUTPUT_RATE_25_HZ                  0b00000001  //  3     0                       25 Hz
#define KX022_1020_OUTPUT_RATE_50_HZ                  0b00000010  //  3     0                       50 Hz
#define KX022_1020_OUTPUT_RATE_100_HZ                 0b00000011  //  3     0                       100 Hz
#define KX022_1020_OUTPUT_RATE_200_HZ                 0b00000100  //  3     0                       200 Hz
#define KX022_1020_OUTPUT_RATE_400_HZ                 0b00000101  //  3     0                       400 Hz    not available in KX022_LOW_POWER
#define KX022_1020_OUTPUT_RATE_800_HZ                 0b00000110  //  3     0                       800 Hz    not available in KX022_LOW_POWER
#define KX022_1020_OUTPUT_RATE_1600_HZ                0b00000111  //  3     0                       1600 Hz   not available in KX022_LOW_POWER
#define KX022_1020_OUTPUT_RATE_0_781_HZ               0b00001000  //  3     0                       0.781 Hz
#define KX022_1020_OUTPUT_RATE_1_563_HZ               0b00001001  //  3     0                       1.563 Hz
#define KX022_1020_OUTPUT_RATE_3_125_HZ               0b00001010  //  3     0                       3.125 Hz
#define KX022_1020_OUTPUT_RATE_6_25_HZ                0b00001011  //  3     0                       6.25 Hz
//KX022_1020_REG_INC1
#define KX022_1020_INT1_DISABLE                       0b00000000  //  5     5     INT output disabled
#define KX022_1020_INT1_ENABLE                        0b00100000  //  5     5     INT output enabled
#define KX022_1020_INT1_ACTIVE_LOW                    0b00000000  //  4     4     INT active low
#define KX022_1020_INT1_ACTIVE_HIGH                   0b00010000  //  4     4     INT active high
#define KX022_1020_INT1_LATCH_ON                      0b00000000  //  3     3     INT will latch until cleared by reading KX022_1020_REG_INT_REL
#define KX022_1020_INT1_LATCH_OFF                     0b00001000  //  3     3     INT will output a single 50 us pulse
//KX022_1020_REG_INC2
#define KX022_1020_INT1_X_NEG_OFF                     0b00000000  //  5     5     negative X value will not trigger interrupt
#define KX022_1020_INT1_X_NEG_ON                      0b00100000  //  5     5     negative X value will trigger interrupt
#define KX022_1020_INT1_X_POS_OFF                     0b00000000  //  4     4     positive X value will not trigger interrupt
#define KX022_1020_INT1_X_POS_ON                      0b00010000  //  4     4     positive X value will trigger interrupt
#define KX022_1020_INT1_Y_NEG_OFF                     0b00000000  //  3     3     negative Y value will not trigger interrupt
#define KX022_1020_INT1_Y_NEG_ON                      0b00001000  //  3     3     negative Y value will trigger interrupt
#define KX022_1020_INT1_Y_POS_OFF                     0b00000000  //  2     2     positive Y value will not trigger interrupt
#define KX022_1020_INT1_Y_POS_ON                      0b00000100  //  2     2     positive Y value will trigger interrupt
#define KX022_1020_INT1_Z_NEG_OFF                     0b00000000  //  1     1     negative Z value will not trigger interrupt
#define KX022_1020_INT1_Z_NEG_ON                      0b00000010  //  1     1     negative Z value will trigger interrupt
#define KX022_1020_INT1_Z_POS_OFF                     0b00000000  //  0     0     positive Z value will not trigger interrupt
#define KX022_1020_INT1_Z_POS_ON                      0b00000001  //  0     0     positive Z value will trigger interrupt
//KX022_1020_REG_INC4
#define KX022_1020_INT1_BUFFER_FULL_OFF               0b00000000  //  6     6     interrupt will not be triggered on full buffer
#define KX022_1020_INT1_BUFFER_FULL_ON                0b01000000  //  6     6     interrupt will be triggered on full buffer
#define KX022_1020_INT1_WATERMARK_OFF                 0b00000000  //  5     5     interrupt will not be triggered on watermark (filled FIFO)
#define KX022_1020_INT1_WATERMARK_ON                  0b00100000  //  5     5     interrupt will be triggered on watermark (filled FIFO)
#define KX022_1020_INT1_DATA_READY_OFF                0b00000000  //  4     4     interrupt will not be triggered when the measured data are ready
#define KX022_1020_INT1_DATA_READY_ON                 0b00010000  //  4     4     interrupt will be triggered when the measured data are ready
#define KX022_1020_INT1_TAP_OFF                       0b00000000  //  2     2     interrupt will not be triggered on tap/double tap detection
#define KX022_1020_INT1_TAP_ON                        0b00000100  //  2     2     interrupt will be triggered on tap/double tap detection
#define KX022_1020_INT1_MOTION_DETECT_OFF             0b00000000  //  1     1     interrupt will not be triggered on motion detection
#define KX022_1020_INT1_MOTION_DETECT_ON              0b00000010  //  1     1     interrupt will be triggered on motion detection
#define KX022_1020_INT1_TILT_OFF                      0b00000000  //  0     0     interrupt will not be triggered on tilt detection
#define KX022_1020_INT1_TILT_ON                       0b00000001  //  0     0     interrupt will be triggered on tilt detection

class KX022_1020 {
  public:
    //Measurement variables
    float x = 0; //X-axis acceleration in g force
    float y = 0; //Y-axis acceleration in g force
    float z = 0; //Z-axis acceleration in g force
    
    //Default constructor
    KX022_1020(uint8_t intNum = INT_NONE, uint8_t address = KX022_1020_DEVICE_ADDRESS_L) {
      _intNum = intNum;
      _address = address;
    }
    
    //Initialization function
    uint8_t init(uint8_t range = KX022_1020_RANGE_4G, uint8_t rate = KX022_1020_OUTPUT_RATE_50_HZ) {
      //disable interrupt
      _intNum = INT_NONE;
      
      //check manufacturer ID
      if(_utils.getRegValue(_address, KX022_1020_REG_WHO_AM_I) != KX022_1020_WHO_AM_I) {
        //if the manufacturer ID does not match cancel initialization
        return(1);
      }
      
      //set control registers according to datasheet and user settings
      _utils.setRegValue(_address, KX022_1020_REG_CNTL1, KX022_1020_STANDBY, 7, 7);
      delay(50); //wait for standby mode
      _utils.setRegValue(_address, KX022_1020_REG_CNTL1, KX022_1020_HIGH_RESOLUTION | KX022_1020_DATA_READY_OFF | range | KX022_1020_TAP_DETECT_OFF | KX022_1020_WAKE_UP_OFF | KX022_1020_TILT_POSITION_OFF, 6, 0);
      _utils.setRegValue(_address, KX022_1020_REG_ODCNTL, KX022_1020_IIR_BYPASS_OFF | KX022_1020_LOW_PASS_FILTER_ODR_9 | rate);
      _utils.setRegValue(_address, KX022_1020_REG_INC1, KX022_1020_INT1_DISABLE, 5, 5);
      _utils.setRegValue(_address, KX022_1020_REG_CNTL1, KX022_1020_OPERATE, 7, 7);
      
      //set sensitivity according to user settings
      switch(range) {
        case KX022_1020_RANGE_2G: { _accelSensitivity = 16384;
                                  } break;
        case KX022_1020_RANGE_4G: { _accelSensitivity = 8192;
                                  } break;
        case KX022_1020_RANGE_8G: { _accelSensitivity = 4096;
                                  } break;
      }
      return(0);
    }
    
    //Initialization function overload with interrupts
    uint8_t init(void func(void), uint8_t range = KX022_1020_RANGE_4G, uint8_t rate = KX022_1020_OUTPUT_RATE_50_HZ) {
      //check manufacturer ID
      if(_utils.getRegValue(_address, KX022_1020_REG_WHO_AM_I) != KX022_1020_WHO_AM_I) {
        //if the manufacturer ID does not match cancel initialization
        return(1);
      }
      
      //interrupt setup
      attachInterrupt(_intNum, func, RISING);
      _flagDrdy = false;
      
      //set control registers according to datasheet and user settings
      _utils.setRegValue(_address, KX022_1020_REG_CNTL1, KX022_1020_STANDBY | KX022_1020_HIGH_RESOLUTION | KX022_1020_DATA_READY_ON | range | KX022_1020_TAP_DETECT_OFF | KX022_1020_WAKE_UP_OFF | KX022_1020_TILT_POSITION_OFF);
      _utils.setRegValue(_address, KX022_1020_REG_ODCNTL, KX022_1020_IIR_BYPASS_OFF | KX022_1020_LOW_PASS_FILTER_ODR_9 | rate);
      _utils.setRegValue(_address, KX022_1020_REG_INC1, KX022_1020_INT1_ENABLE | KX022_1020_INT1_ACTIVE_HIGH | KX022_1020_INT1_LATCH_OFF, 5, 3);
      _utils.setRegValue(_address, KX022_1020_REG_INC4, KX022_1020_INT1_DATA_READY_ON, 4, 4);
      _utils.setRegValue(_address, KX022_1020_REG_CNTL1, KX022_1020_OPERATE, 7, 7);
      
      //set sensitivity according to user settings
      switch(range) {
        case KX022_1020_RANGE_2G: { _accelSensitivity = 16384;
                                  } break;
        case KX022_1020_RANGE_4G: { _accelSensitivity = 8192;
                                  } break;
        case KX022_1020_RANGE_8G: { _accelSensitivity = 4096;
                                  } break;
      }
      return(0);
    }
    
    //Measurement function
    uint8_t measure(void) {
      //if interrupts are used, check DRDY flag
      if(_intNum != INT_NONE) {
        //if the flag is present, read the measured value as 2-byte integer and calculate the real acceleration in g force
        if(_flagDrdy) {
          x = (float)((_utils.getRegValue(_address, KX022_1020_REG_XOUTH) << 8) | _utils.getRegValue(_address, KX022_1020_REG_XOUTL)) / (float)_accelSensitivity;
          y = (float)((_utils.getRegValue(_address, KX022_1020_REG_YOUTH) << 8) | _utils.getRegValue(_address, KX022_1020_REG_YOUTL)) / (float)_accelSensitivity;
          z = (float)((_utils.getRegValue(_address, KX022_1020_REG_ZOUTH) << 8) | _utils.getRegValue(_address, KX022_1020_REG_ZOUTL)) / (float)_accelSensitivity;
        
          //reset flag
          _flagDrdy = false;
        
          //acceleration values were successfully updated, return 0
          return(0);
        }
      } else {
        //read the measured value as 2-byte integer and calculate the real acceleration in g force
        x = (float)((_utils.getRegValue(_address, KX022_1020_REG_XOUTH) << 8) | _utils.getRegValue(_address, KX022_1020_REG_XOUTL)) / (float)_accelSensitivity;
        y = (float)((_utils.getRegValue(_address, KX022_1020_REG_YOUTH) << 8) | _utils.getRegValue(_address, KX022_1020_REG_YOUTL)) / (float)_accelSensitivity;
        z = (float)((_utils.getRegValue(_address, KX022_1020_REG_ZOUTH) << 8) | _utils.getRegValue(_address, KX022_1020_REG_ZOUTL)) / (float)_accelSensitivity;
        
        //acceleration values were successfully updated, return 0
        return(0);
      }
      
      //acceleration values were not updated, return 1
      return(1);
    }
    
    //TODO: implement interrupts for value, tilt, tap, etc.
    
    //Function to be called inside ISR, this will set data ready flag
    volatile void setFlagDrdy(void) {
      _flagDrdy = true;
    }
  
  private:
    utilities _utils;
    uint8_t _address, _intNum;
    uint16_t _accelSensitivity = 8192;
    volatile bool _flagDrdy = false;
};

#endif
