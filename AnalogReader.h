#ifndef AnalogReader_h
#define AnalogReader_h
#include "Arduino.h"

class AnalogReader{
  public:
    AnalogReader(int16_t outputRangeMin, int16_t outputRangeMax, uint16_t recentValuesAmount, uint8_t pin, uint16_t readMin, uint16_t readMax);
    uint16_t getCurrentValueRaw();
    int16_t getCurrentValue();
    void setOutputRange(int16_t rangeMin, int16_t rangeMax);
    int16_t getOutputRangeMax();
    int16_t getOutputRangeMin();
    boolean update();
    void setPin(uint8_t pin);
    
  private:
    uint8_t _pin;
    uint16_t _readMin;
    uint16_t _readMax;
    uint16_t _currentValue;
    uint16_t _recentValuesAmount;
    uint16_t *_recentValues;
    uint16_t _noiseThreshold;
    int16_t _outputRangeMin;
    int16_t _outputRangeMax;
};

#endif
