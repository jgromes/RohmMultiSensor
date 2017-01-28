#ifndef _BD7411G_CPP
#define _BD7411G_CPP

class BD7411G {
  public:
    BD7411G(void) {}
    
    int init(uint8_t pin = 0) {
      _pin = pin;
    }
    
    bool measure() {
      if(digitalRead(_pin) == 0) {
        return(true);
      } else {
        return(false);
      }
    }
  private:
    uint8_t _pin;
};

#endif