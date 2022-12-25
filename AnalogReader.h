#ifndef AnalogReader_h
#define AnalogReader_h
#include "Arduino.h"

class AnalogReader{
  public:
    // Creates instance of analog reader
    AnalogReader(
      int16_t outputRangeMin, // determines minimal output value
      int16_t outputRangeMax, // determines maximal output value
      uint16_t recentValuesAmount, // how many values from previous reads should be held to calculate avreage (the bigger the value, the better noise filtering, but the slower reaction to change) 
      uint8_t pin, // pin to read from
      uint16_t readMin, // minimal value analog can provide
      uint16_t readMax // maximal value analog can provide
    );
  
    // get current value not mapped to outputRangeMin;outputRangeMax
    uint16_t getCurrentValueRaw();
  
    // get current value mapped to outputRangeMin;outputRangeMax
    int16_t getCurrentValue();
  
    // sets output range
    void setOutputRange(int16_t rangeMin, int16_t rangeMax);
  
    int16_t getOutputRangeMax();
  
    int16_t getOutputRangeMin();
  
    // this function updates analog reader values, and should get called as often as possible
    // returns true, if mapped value got changed
    boolean update();
  
    // sets pin to read analog input from
    void setPin(uint8_t pin);
    
  private:
    uint8_t _pin;
    uint16_t _readMin;
    uint16_t _readMax;
    uint16_t _currentValue;
    uint16_t _recentValuesAmount;
    uint16_t _recentValues[25];
    uint16_t _noiseThreshold;
    int16_t _outputRangeMin;
    int16_t _outputRangeMax;
};

#endif
