#ifndef _BH1745NUC_CPP
#define _BH1745NUC_CPP

//BH1745NUC register map
#define BH1745NUC_REG_SYSTEM_CONTROL                  0x40
#define BH1745NUC_REG_MODE_CONTROL_1                  0x41
#define BH1745NUC_REG_MODE_CONTROL_2                  0x42
#define BH1745NUC_REG_MODE_CONTROL_3                  0x43
#define BH1745NUC_REG_RED_DATA_LSB                    0x50
#define BH1745NUC_REG_RED_DATA_MSB                    0x51
#define BH1745NUC_REG_GREEN_DATA_LSB                  0x52
#define BH1745NUC_REG_GREEN_DATA_MSB                  0x53
#define BH1745NUC_REG_BLUE_DATA_LSB                   0x54
#define BH1745NUC_REG_BLUE_DATA_MSB                   0x55
#define BH1745NUC_REG_CLEAR_DATA_LSB                  0x56
#define BH1745NUC_REG_CLEAR_DATA_MSB                  0x57
#define BH1745NUC_REG_DINT_DATA_LSB                   0x58
#define BH1745NUC_REG_DINT_DATA_MSB                   0x59
#define BH1745NUC_REG_INTERRUPT                       0x60
#define BH1745NUC_REG_PERSISTENCE                     0x61
#define BH1745NUC_REG_TH_LSB                          0x62
#define BH1745NUC_REG_TH_MSB                          0x63
#define BH1745NUC_REG_TL_LSB                          0x64
#define BH1745NUC_REG_TL_MSB                          0x65
#define BH1745NUC_REG_MANUFACTURER_ID                 0x92

//BH1745NUC default values
#define BH1745NUC_DEVICE_ADDRESS_L                    0x38
#define BH1745NUC_DEVICE_ADDRESS_H                    0x39
#define BH1745NUC_PART_ID                             0x0B
#define BH1745NUC_MANUFACTURER_ID                     0xE0

//BH1745NUC settings
//BH1745NUC_REG_MODE_CONTROL_1                                        MSB   LSB   DESCRIPTION
#define BH1745NUC_MEAS_TIME_160_MS                    0b00000000  //  2     0     measurement time: 160 ms
#define BH1745NUC_MEAS_TIME_320_MS                    0b00000001  //  2     0                       320 ms
#define BH1745NUC_MEAS_TIME_640_MS                    0b00000010  //  2     0                       640 ms
#define BH1745NUC_MEAS_TIME_1280_MS                   0b00000011  //  2     0                       1280 ms
#define BH1745NUC_MEAS_TIME_2560_MS                   0b00000100  //  2     0                       2560 ms
#define BH1745NUC_MEAS_TIME_5120_MS                   0b00000101  //  2     0                       5120 ms
//BH1745NUC_REG_MODE_CONTROL_2
#define BH1745NUC_RGBC_OFF                            0b00000000  //  4     4     RGBC measurement disabled
#define BH1745NUC_RGBC_ON                             0b00010000  //  4     4     RGBC measurement enabled
#define BH1745NUC_ADC_GAIN_1                          0b00000000  //  1     0     measurement gain: 1x
#define BH1745NUC_ADC_GAIN_2                          0b00000001  //  1     0                       2x
#define BH1745NUC_ADC_GAIN_16                         0b00000010  //  1     0                       16x
//BH1745NUC_REG_MODE_CONTROL_3
#define BH1745NUC_MODE_CONTROL_3                      0b00000010

class BH1745NUC {
  public:
    //Default constructor
    BH1745NUC(uint8_t address = BH1745NUC_DEVICE_ADDRESS_H) {
      _address = address;
    }
    
    //Initialization function
    uint8_t init(uint8_t measurementTime = BH1745NUC_MEAS_TIME_160_MS) {
      //check manufacturer and part ID
      if((_utils.getRegValue(_address, BH1745NUC_REG_SYSTEM_CONTROL, 5, 0) != BH1745NUC_PART_ID) || (_utils.getRegValue(_address, BH1745NUC_REG_MANUFACTURER_ID) != BH1745NUC_MANUFACTURER_ID)) {
        //if the IDs do not match cancel initialization
        return(1);
      }
      
      //set control registers according to datasheet and user settings
      _utils.setRegValue(_address, BH1745NUC_REG_MODE_CONTROL_1, measurementTime, 2, 0);
      _utils.setRegValue(_address, BH1745NUC_REG_MODE_CONTROL_2, BH1745NUC_RGBC_ON | BH1745NUC_ADC_GAIN_16, 4, 0);
      _utils.setRegValue(_address, BH1745NUC_REG_MODE_CONTROL_3, BH1745NUC_MODE_CONTROL_3);;
      
      return(0);
    }
    
    //Measurement function
    uint16_t* measure(void) {
      uint16_t* value = new uint16_t[4];
      
      //TODO: implement interrupt
      
      //read measured RGBC value
      value[0] = ((uint16_t)_utils.getRegValue(_address, BH1745NUC_REG_RED_DATA_MSB) << 8) | _utils.getRegValue(_address, BH1745NUC_REG_RED_DATA_LSB);
      value[1] = ((uint16_t)_utils.getRegValue(_address, BH1745NUC_REG_GREEN_DATA_MSB) << 8) | _utils.getRegValue(_address, BH1745NUC_REG_GREEN_DATA_LSB);
      value[2] = ((uint16_t)_utils.getRegValue(_address, BH1745NUC_REG_BLUE_DATA_MSB) << 8) | _utils.getRegValue(_address, BH1745NUC_REG_BLUE_DATA_LSB);
      value[3] = ((uint16_t)_utils.getRegValue(_address, BH1745NUC_REG_CLEAR_DATA_MSB) << 8) | _utils.getRegValue(_address, BH1745NUC_REG_CLEAR_DATA_LSB);
      
      return(value);
    }
  
  private:
    utilities _utils;
    uint8_t _address;
};

#endif
