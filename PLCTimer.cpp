#include "PLCTimer.h"

PLCTimer::PLCTimer(Type type){
    _type = type; //this is the type of timer. TON or TOF
    _previous = 0;
};


uint8_t PLCTimer::run(uint8_t In, uint32_t preset) {
    uint8_t tt;
    uint32_t et;
    return run(In, preset, &et, &tt);
};

uint8_t PLCTimer::run(uint8_t In, uint32_t preset, uint32_t* elapsedTime) {
    return run(In, preset, elapsedTime);
};


uint8_t PLCTimer::run(uint8_t In, uint32_t preset, uint32_t* elapsedTime, uint8_t *timing) {
    uint8_t retVal = 0;
    /*The type of the timer defines what level the In signal must have to start the timer
    If it's a TON, the trigger is from low to high. 
    It it's a TOF, the trigger is from high to low.     
    */
    //Serial.println(In);
    //Serial.println(_previous);
    if (In ==_type && _previous != In) {
        _startTime = _elTime = millis(); //record the starting point. 
        _timing = true; 
    };
    /*
    If the signal goes low and the timer was active, then reset. 
    */
    if (In !=_type && _previous != In) {
        _timing = false;
        _done = false; 
    };
    /*time ended and time is running... */
    if ((millis() - _startTime >= preset) && _timing) {
        _done = true; 
        _elTime = millis();
        _timing = false;
    } 
    
    /*
    update variables
    */
    if (_timing) _elapsedTime = millis() - _startTime;
    else _elapsedTime = 0;//_elTime - _startTime; 
    
    *timing = _timing; 
    *elapsedTime = _elapsedTime;
    _previous = In; //record the previous state. 
    
    if (_type == TON) 
        retVal = In && !_timing;
    else
        retVal = In || _timing;
    return retVal;//_done;
};

//to be confirmed how it is to be used. 
uint8_t PLCTimer::reset(){
    _startTime = millis();
    _done = false;
    return 1;
};


/*
TOF 
_done = In && _timing

TON
_done = In && not _timing

*/
