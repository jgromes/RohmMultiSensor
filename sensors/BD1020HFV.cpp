#ifndef _BD1020HFV_CPP
#define _BD1020HFV_CPP

#define ANALOG_1  A0
#define ANALOG_2  A1

class BD1020HFV {
  public:
    BD1020HFV(void) {}
    
    uint8_t init(uint8_t position = ANALOG_1) {
      _position = position;
      return 0;
    }
    
    float measure(void) {
      uint16_t rawValue;
      float value;
      rawValue = analogRead(_position);
      value = -(1000 * ((float)rawValue * 5 / 1024) - 1546) / 8.2;
      return(value);
    }
  private:
    uint8_t _position;
};

#endif
