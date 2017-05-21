#ifndef _BD7411G_CPP
#define _BD7411G_CPP

class BD7411G {
  public:
    //Measurement variables
    bool mf = false; //magnetic field presence
    
    //Default constructor
    BD7411G(void) {}
    
    //Initialization function
    uint8_t init(uint8_t pin = 0) {
      _pin = pin;
      return 0;
    }
    
    //Measurement function
    uint8_t measure() {
      //if the sensor output is LOW, magnetic field was detected
      if(digitalRead(_pin) == 0) {
        mf = true;
      } else {
        mf = false;
      }
      
      return(0);
    }
  
  private:
    uint8_t _pin;
};

#endif
