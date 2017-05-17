#ifndef _UTILITIES_CPP
#define _UTILITIES_CPP

class utilities {
  public:
    //Default constructor
    utilities(void) {}
    
    //Function for getting specific bits in register
    //this function will only read bit range from msb to lsb, the returned value will be zero-padded
    uint8_t getRegValue(uint8_t deviceAddress, uint8_t reg, uint8_t msb = 7, uint8_t lsb = 0) {
      if((msb > 7) || (lsb > 7) || (lsb > msb)) {
        return 0xFF;
      }
      
      uint8_t rawValue = readRegister(deviceAddress, reg);
      uint8_t maskedValue = rawValue & ((0b11111111 << lsb) | (0b11111111 >> (7 - msb)));
      
      return(maskedValue);
    }
    
    //Function for setting specific bits in register
    //this function will only change bit range from msb to lsb
    uint8_t setRegValue(uint8_t deviceAddress, uint8_t reg, uint8_t value, uint8_t msb = 7, uint8_t lsb = 0) {
      if((msb > 7) || (lsb > 7) || (lsb > msb)) {
        return 0xFF;
      }
      
      uint8_t currentValue = readRegister(deviceAddress, reg);
      uint8_t newValue = currentValue & ((0b11111111 << (msb + 1)) | (0b11111111 >> (8 - lsb)));
      
      writeRegister(deviceAddress, reg, newValue | value);
    }
    
    //Function for reading from several consecutive registers
    uint8_t* readRegisterBurst(uint8_t deviceAddress, uint8_t reg, uint8_t len) {
      uint8_t* inBytes = new uint8_t[len];
      
      Wire.beginTransmission(deviceAddress);
      Wire.write(reg);
      Wire.endTransmission(false);
      
      Wire.requestFrom(deviceAddress, len);
      
      uint8_t i;
      while(Wire.available()) {
        inBytes[i++] = Wire.read();
      }
      
      return inBytes;
    }
    
    //Function for writing to several consecutive registers
    void writeRegisterBurst(uint8_t deviceAddress, uint8_t reg, uint8_t data, uint8_t len) {
      Wire.beginTransmission(deviceAddress);
      Wire.write(reg);
      Wire.write(data, len);
      Wire.endTransmission(true);
    }
    
    //Function for reading from a single register
    //this is a low-level function, use getRegValue instead!
    uint8_t readRegister(uint8_t deviceAddress, uint8_t reg) {
      uint8_t inByte;
  
      Wire.beginTransmission(deviceAddress);
      Wire.write(reg);
      Wire.endTransmission(false);
      
      Wire.requestFrom(deviceAddress, (uint8_t)1);
      inByte = Wire.read();
      
      return(inByte);
    }
    
    //Function for writing to a single register
    //this is a low-level function, use setRegValue instead!
    void writeRegister(uint8_t deviceAddress, uint8_t reg, uint8_t data) {
      Wire.beginTransmission(deviceAddress);
      Wire.write(reg);
      Wire.write(data);
      Wire.endTransmission(true);
    }
};

#endif
