#ifndef AnalogReader_h
#define AnalogReader_h
#include "Arduino.h"

class AnalogReader{
  public:
    AnalogReader(uint16_t noiseThreshold, uint16_t recentValuesAmount, uint8_t pin, uint16_t readMin, uint16_t readMax);
    uint16_t getCurrentValue();
    uint16_t getCurrentValueMapped(uint16_t min, uint16_t max);
    uint16_t getReadMax();
    uint16_t getReadMin();
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
};

#endif
