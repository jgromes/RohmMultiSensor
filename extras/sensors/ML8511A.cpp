#ifndef _ROHM_MULTI_SENSOR_ML8511A_CPP
#define _ROHM_MULTI_SENSOR_ML8511A_CPP

#define ANALOG_1  A0
#define ANALOG_2  A2

class ML8511A: public Sensor {
  public:
    //Measurement variables
    float uvRad = 0; //UV radiation intensity in mW/cm^2
    
    //Default constructor
    ML8511A(uint8_t position = ANALOG_1) {
      _position = position;
    }
    
    //Initialization function
    uint8_t init(void) {
      return(0);
    }
    
    //Measurement function
    uint8_t measure(void) {
      uint16_t rawValue;
      
      //read the analog value
      rawValue = analogRead(_position);
      
      //calculate real radiation intensity in mW/cm^2
      uvRad = 25 * (((float)rawValue * 5 / 1024) - 1) / 3;
      
      //real radiation intensity cannot be less than zero
      if(uvRad < 0) {
        uvRad = 0;
      }
      
      return(0);
    }
  
  private:
    uint8_t _position;
};

#endif
