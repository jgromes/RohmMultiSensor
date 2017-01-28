#ifndef _BM1383GLV_CPP
#define _BM1383GLV_CPP

//BM1383GLV register map
#define BM1383GLV_REG_ID                              0x10
#define BM1383GLV_REG_RESET_CONTROL                   0x11
#define BM1383GLV_REG_POWER_DOWN                      0x12
#define BM1383GLV_REG_RESET                           0x13
#define BM1383GLV_REG_MODE_CONTROL                    0x14
#define BM1383GLV_REG_INT_H_TH_MSB                    0x15
#define BM1383GLV_REG_INT_H_TH_LSB                    0x16
#define BM1383GLV_REG_INT_L_TH_MSB                    0x17
#define BM1383GLV_REG_INT_L_TH_LSB                    0x18
#define BM1383GLV_REG_INT_CONTROL                     0x19
#define BM1383GLV_REG_PRESSURE_MSB                    0x1C
#define BM1383GLV_REG_PRESSURE_MID                    0x1D
#define BM1383GLV_REG_PRESSURE_LSB                    0x1F

//BM1383GLV default values
#define BM1383GLV_DEVICE_ADDRESS                      0x5D
#define BM1383GLV_ID                                  0x31

//BM1383GLV settings
//BM1383GLV_REG_RESET                                                 MSB   LSB   DESCRIPTION
#define BM1383GLV_RSTB_RESET                          0b00000000  //  0     0     measurement control block reset
#define BM1383GLV_RSTB_ACTIVE                         0b00000001  //  0     0     measurement control block active
//BM1383GLV_REG_POWER_DOWN
#define BM1383GLV_POWER_DOWN                          0b00000000  //  0     0     power down
#define BM1383GLV_ACTIVE                              0b00000001  //  0     0     active
//BM1383GLV_REG_MODE_CONTROL
#define BM1383GLV_AVERAGE_1                           0b00000000  //  7     5     number of pressure measurements to average: 1
#define BM1383GLV_AVERAGE_2                           0b00100000  //  7     5                                                 2
#define BM1383GLV_AVERAGE_4                           0b01000000  //  7     5                                                 4
#define BM1383GLV_AVERAGE_8                           0b01100000  //  7     5                                                 8
#define BM1383GLV_AVERAGE_16                          0b10000000  //  7     5                                                 16
#define BM1383GLV_AVERAGE_32                          0b10100000  //  7     5                                                 32
#define BM1383GLV_AVERAGE_64                          0b11000000  //  7     5                                                 64
#define BM1383GLV_LESS_TEMP_OFF                       0b00000000  //  3     3     temperature will be measured as often as pressure
#define BM1383GLV_LESS_TEMP_ON                        0b00001000  //  3     3     temperature will be measured 4 times less frequently than pressure
#define BM1383GLV_STANDBY                             0b00000000  //  2     0     measurement mode: standby
#define BM1383GLV_ONE_SHOT                            0b00000001  //  2     0                       one-shot
#define BM1383GLV_CONTINUOUS_50_MS                    0b00000010  //  2     0                       continuous over 50 ms
#define BM1383GLV_CONTINUOUS_100_MS                   0b00000011  //  2     0                       continuous over 100 ms
#define BM1383GLV_CONTINUOUS_200_MS                   0b00000100  //  2     0                       continuous over 200 ms

class BM1383GLV {
  public:
    BM1383GLV(uint8_t address = BM1383GLV_DEVICE_ADDRESS) {
      _address = address;
    }
    
    int init(uint8_t mode = BM1383GLV_CONTINUOUS_200_MS, uint8_t avg = BM1383GLV_AVERAGE_64, uint8_t tempAvg = BM1383GLV_LESS_TEMP_ON) {
      if(_utils.getRegValue(_address, BM1383GLV_REG_ID) != BM1383GLV_ID) {
        return(-1);
      }
      _utils.setRegValue(_address, BM1383GLV_REG_POWER_DOWN, BM1383GLV_ACTIVE, 0, 0);
      _utils.setRegValue(_address, BM1383GLV_REG_RESET, BM1383GLV_RSTB_ACTIVE, 0, 0);
      _utils.setRegValue(_address, BM1383GLV_REG_MODE_CONTROL, avg | tempAvg | mode);
      return(0);
    }
    
    float measure(void) {
      uint32_t rawValue;
      float value;
      rawValue = (((uint32_t)_utils.getRegValue(_address, BM1383GLV_REG_PRESSURE_MSB) << 16) | ((uint32_t)_utils.getRegValue(_address, BM1383GLV_REG_PRESSURE_MID) << 8) | _utils.getRegValue(_address, BM1383GLV_REG_PRESSURE_LSB, 7, 2)) >> 2;
      value = rawValue / 2048.0;
      return(value);
    }
  private:
    utilities _utils;
    uint8_t _address;
};

#endif