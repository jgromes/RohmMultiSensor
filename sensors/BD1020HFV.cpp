#ifndef _BD1020HFV_CPP
#define _BD1020HFV_CPP

#define ANALOG_1  A0
#define ANALOG_2  A2

class BD1020HFV {
  public:
    //Default constructor
    BD1020HFV(uint8_t position = ANALOG_1) {
      _position = position;
    }
    
    //Initialization function
    uint8_t init(void) {
      return 0;
    }
    
    //Measurement function
    float measure(void) {
      uint16_t rawValue;
      float value;
      
      //read the analog value
      rawValue = analogRead(_position);
      
      //calculate real temperature in deg. C
      value = -(1000 * ((float)rawValue * 5 / 1024) - 1546) / 8.2;
      
      return(value);
    }
  
  private:
    uint8_t _position;
};

#endif
