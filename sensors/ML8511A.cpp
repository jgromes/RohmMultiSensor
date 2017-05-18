#ifndef _ML8511A_CPP
#define _ML8511A_CPP

#define ANALOG_1  A0
#define ANALOG_2  A1

class ML8511A {
  public:
    //Default constructor
    ML8511A(uint8_t position = ANALOG_1) {
      _position = position;
    }
    
    //Initialization function
    uint8_t init(void) {
      return(0);
    }
    
    //Measurement function
    float measure(void) {
      uint16_t rawValue;
      float value;
      
      //read the analog value
      rawValue = analogRead(_position);
      
      //calculate real radiation intensity in mW/cm^2
      value = 25 * (((float)rawValue * 5 / 1024) - 1) / 3;
      
      //real radiation intensity cannot be less than zero
      if(value < 0) {
        value = 0;
      }
      
      return(value);
    }
  
  private:
    uint8_t _position;
};

#endif
