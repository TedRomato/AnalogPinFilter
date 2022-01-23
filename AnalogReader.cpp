#include "Arduino.h"
#include "AnalogReader.h"


// noiseThreshold - a range in which read value is considered noise
// recentValuesAmount - how many values are remembered in the array -> the more the slower responsivnes, but better filtering
// pin - analog pin to read from 
// readMin - minimal value that can be consistently read
// readMax - maximal value that can be consistently read

AnalogReader::AnalogReader(uint16_t noiseThreshold, uint16_t recentValuesAmount, uint8_t pin, uint16_t readMin, uint16_t readMax)
{
  _readMin = readMin;
  _readMax = readMax; 
  _noiseThreshold = noiseThreshold;
  _recentValuesAmount = recentValuesAmount;
  _pin = pin;
  _recentValues = malloc(sizeof(uint16_t) * _recentValuesAmount); 

  memset(_recentValues, 0, sizeof(uint16_t) * _recentValuesAmount);
}


uint16_t AnalogReader::getCurrentValue()
{
  return _currentValue;
}

uint16_t AnalogReader::getCurrentValueMapped(uint16_t min, uint16_t max)
{
  return map(this->getCurrentValue(), this->getReadMin(), this->getReadMax(), min, max);
}


uint16_t AnalogReader::getReadMin()
{
  return _readMin;
}

uint16_t AnalogReader::getReadMax()
{
  return _readMax;
}

void AnalogReader::setPin(uint8_t pin)
{
  _pin = pin;
}



// returns true if new value is loaded to _currentValue, otherwise returns false
boolean AnalogReader::update()
{  
  uint16_t analogVal = analogRead(_pin);
  if(analogVal < _readMin){
    analogVal = _readMin;
  } else if(analogVal > _readMax) {
    analogVal = _readMax;
  }


  // we get the sum of the new array, to calculate new average
  int accumulator = 0;
  // we shift array left, to remove the oldest (least relevant) value, and add new to the last index
  for(int i = 1; i < _recentValuesAmount; ++i){
    _recentValues[i - 1] = _recentValues[i];
    accumulator += _recentValues[i];
  }
  _recentValues[_recentValuesAmount - 1] = analogVal;

  accumulator += analogVal;

  // we calculate average to see, if we are above noise threshold
  int avg = accumulator/_recentValuesAmount;
  if(avg > _currentValue + _noiseThreshold || avg < _currentValue - _noiseThreshold){
    _currentValue = avg;
    return true;
  } else if((avg == _readMin || avg == _readMax) && _currentValue != avg) {
    _currentValue = avg;
    return true;
  }
  
  return false;
} 
