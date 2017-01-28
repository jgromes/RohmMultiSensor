#ifndef _UTILITIES_CPP
#define _UTILITIES_CPP


class utilities {
  public:
    utilities(void) {}
    
    uint8_t setRegValue(uint8_t deviceAddress, uint8_t reg, uint8_t value, uint8_t msb = 7, uint8_t lsb = 0) {
      if((msb > 7) || (lsb > 7) || (lsb > msb)) {
        return 0xFF;
      }
      uint8_t currentValue = readRegister(deviceAddress, reg);
      uint8_t newValue = currentValue & ((0b11111111 << (msb + 1)) | (0b11111111 >> (8 - lsb)));
      writeRegister(deviceAddress, reg, newValue | value);
    }
    
    uint8_t getRegValue(uint8_t deviceAddress, uint8_t reg, uint8_t msb = 7, uint8_t lsb = 0) {
      if((msb > 7) || (lsb > 7) || (lsb > msb)) {
        return 0xFF;
      }
      uint8_t rawValue = readRegister(deviceAddress, reg);
      uint8_t maskedValue = rawValue & ((0b11111111 << lsb) | (0b11111111 >> (7 - msb)));
      return(maskedValue);
    }
    
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
    
    /*void writeRegisterBurst(uint8_t deviceAddress, uint8_t reg, uint8_t data, uint8_t len) {
      Wire.beginTransmission(deviceAddress);
      Wire.write(reg);
      Wire.write(data, len);
      Wire.endTransmission(true);
    }*/
    
    uint8_t readRegister(uint8_t deviceAddress, uint8_t reg) {
      uint8_t inByte;
  
      Wire.beginTransmission(deviceAddress);
      Wire.write(reg);
      Wire.endTransmission(false);
      
      Wire.requestFrom(deviceAddress, (uint8_t)1);
      //while(!Wire.available());
      inByte = Wire.read();
      
      return(inByte);
    }
    
    void writeRegister(uint8_t deviceAddress, uint8_t reg, uint8_t data) {
      Wire.beginTransmission(deviceAddress);
      Wire.write(reg);
      Wire.write(data);
      Wire.endTransmission(true);
    }
};

#endif
