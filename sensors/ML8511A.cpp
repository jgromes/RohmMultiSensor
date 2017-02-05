#ifndef _ML8511A_CPP
#define _ML8511A_CPP

#define ANALOG_1  A0
#define ANALOG_2  A1

class ML8511A {
  public:
    ML8511A(void) {}
    
    uint8_t init(uint8_t pin = ANALOG_1) {
      _pin = pin;
      return(0);
    }
    
    float measure(void) {
      uint16_t rawValue;
      float value;
      rawValue = analogRead(_pin);
      value = 25 * (((float)rawValue * 5 / 1024) - 1) / 3;
      if(value < 0) {
        value = 0;
      }
      return(value);
    }
  private:
    uint8_t _pin;
};

#endif
