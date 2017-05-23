#ifndef _BH1790GLC_CPP
#define _BH1790GLC_CPP

//BH1790GLC register map
#define BH1790GLC_REG_MANUFACTURER_ID                 0x0F
#define BH1790GLC_REG_PART_ID                         0x10
#define BH1790GLC_REG_RESET                           0x40
#define BH1790GLC_REG_MEAS_CONTROL_1                  0x41
#define BH1790GLC_REG_MEAS_CONTROL_2                  0x42
#define BH1790GLC_REG_MEAS_START                      0x43
#define BH1790GLC_REG_DATAOUT_LEDOFF_LSB              0x54
#define BH1790GLC_REG_DATAOUT_LEDOFF_MSB              0x55
#define BH1790GLC_REG_DATAOUT_LEDON_LSB               0x56
#define BH1790GLC_REG_DATAOUT_LEDON_MSB               0x57

//BH1790GLC default values
#define BH1790GLC_DEVICE_ADDRESS                      0x5B
#define BH1790GLC_MANUFACTURER_ID                     0xE0
#define BH1790GLC_PART_ID                             0x0D

//BH1790GLC settings
//BH1790GLC_REG_MEAS_CONTROL_1                                        MSB   LSB   DESCRIPTION
#define BH1790GLC_READY                               0b10000000  //  7     7     ready sensor, activate OSC block
#define BH1790GLC_LED_LIGHTING_FREQ_128_HZ            0b00000000  //  2     2     LED frequency:  128 Hz
#define BH1790GLC_LED_LIGHTING_FREQ_64_HZ             0b00000100  //  2     2                     64 Hz
#define BH1790GLC_RCYCLE_64_HZ                        0b00000001  //  1     0     reading cycle frequency:  64 Hz
#define BH1790GLC_RCYCLE_32_HZ                        0b00000010  //  1     0                               32 Hz
//BH1790GLC_REG_MEAS_CONTROL_2
#define BH1790GLC_LED_MODE_PULSE_PULSE                0b00000000  //  7     6     LED driver mode:  LED1 pulse, LED2 pulse
#define BH1790GLC_LED_MODE_CONST_PULSE                0b01000000  //  7     6                       LED1 constant, LED2 pulse
#define BH1790GLC_LED_MODE_PULSE_CONST                0b10000000  //  7     6                       LED1 pulse, LED2 constant
#define BH1790GLC_LED_MODE_CONST_CONST                0b11000000  //  7     6                       LED1 constant, LED2 constant
#define BH1790GLC_LED_ON_TIME_0_3_MS                  0b00000000  //  5     5     LED emitting  time: 0.3 ms
#define BH1790GLC_LED_ON_TIME_0_6_MS                  0b00100000  //  5     5                         0.6 ms
#define BH1790GLC_LED_CURRENT_0_MA                    0b00000000  //  3     0     LED current:  0 mA
#define BH1790GLC_LED_CURRENT_1_MA                    0b00001000  //  3     0                   1 mA
#define BH1790GLC_LED_CURRENT_2_MA                    0b00001001  //  3     0                   2 mA
#define BH1790GLC_LED_CURRENT_3_MA                    0b00001010  //  3     0                   3 mA
#define BH1790GLC_LED_CURRENT_6_MA                    0b00001011  //  3     0                   6 mA
#define BH1790GLC_LED_CURRENT_10_MA                   0b00001100  //  3     0                   10 mA
#define BH1790GLC_LED_CURRENT_20_MA                   0b00001101  //  3     0                   20 mA
#define BH1790GLC_LED_CURRENT_30_MA                   0b00001110  //  3     0                   30 mA
#define BH1790GLC_LED_CURRENT_60_MA                   0b00001111  //  3     0                   60 mA
//BH1790GLC_REG_MEAS_START
#define BH1790GLC_START                               0b00000001  //  0     0     start measurement

class BH1790GLC {
  public:
    //Measurement variables
    int ledOn = 0;//LED-on data
    int ledOff = 0;//LED-off data
    
    //Default constructor
    BH1790GLC(uint8_t address = BH1790GLC_DEVICE_ADDRESS) {
      _address = address;
    }
    
    //Initialization function
    uint8_t init(uint8_t readCycle = BH1790GLC_RCYCLE_32_HZ, uint8_t ledCurrent = BH1790GLC_LED_CURRENT_6_MA) {
      //check manufacturer and part ID
      if((_utils.getRegValue(_address, BH1790GLC_REG_MANUFACTURER_ID) != BH1790GLC_MANUFACTURER_ID) || (_utils.getRegValue(_address, BH1790GLC_REG_PART_ID) != BH1790GLC_PART_ID)) {
        //if the IDs do not match cancel initialization
        return(1);
      }
      
      //set control registers according to datasheet and user settings
      _utils.setRegValue(_address, BH1790GLC_REG_MEAS_CONTROL_1, BH1790GLC_READY | BH1790GLC_LED_LIGHTING_FREQ_128_HZ | readCycle);
      _utils.setRegValue(_address, BH1790GLC_REG_MEAS_CONTROL_2, BH1790GLC_LED_MODE_PULSE_PULSE | BH1790GLC_LED_ON_TIME_0_3_MS | ledCurrent);
      _utils.setRegValue(_address, BH1790GLC_REG_MEAS_START, BH1790GLC_START, 0, 0);
      
      return(0);
    }
    
    //Measurement function
    uint8_t measure(void) {
      uint8_t rawValue[4];
      
      //read the single byte led on/off data
      rawValue[0] = _utils.getRegValue(_address, BH1790GLC_REG_DATAOUT_LEDOFF_LSB);
      rawValue[1] = _utils.getRegValue(_address, BH1790GLC_REG_DATAOUT_LEDOFF_MSB);
      rawValue[2] = _utils.getRegValue(_address, BH1790GLC_REG_DATAOUT_LEDON_LSB);
      rawValue[3] = _utils.getRegValue(_address, BH1790GLC_REG_DATAOUT_LEDON_MSB);
      
      //convert raw data to 2-byte integer
      ledOn = ((int)rawValue[3] << 8) | rawValue[2];
      ledOff = ((int)rawValue[1] << 8) | rawValue[0];
      
      return(0);
    }
  
  private:
    utilities _utils;
    uint8_t _address;
};

#endif
