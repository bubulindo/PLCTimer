#include "Arduino.h"

#ifndef PLCTimer_h
#define PLCTimer_h




// library interface description
class PLCTimer
{
  // user-accessible "public" interface
  public:
  
    enum Type{
        TON = 1,
        TOF = 0
    };
    PLCTimer(Type type); //define the timer as TON, TOF, etc... 

    uint8_t run (uint8_t In, uint32_t preset);

    uint8_t run (uint8_t In, uint32_t preset, uint32_t* elapsedTime);
    
    uint8_t run (uint8_t In, uint32_t preset, uint32_t* elapsedTime, uint8_t* timing);

    uint8_t reset();

    
  private:
    uint8_t _done = 0;
    uint32_t _startTime; 
    uint32_t _elTime; 
    uint32_t _elapsedTime;
    uint8_t _previous = 0;
    uint8_t _type = PLCTimer::TON;
    uint8_t _timing = false;
};

#endif
