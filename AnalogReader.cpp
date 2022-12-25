#include "Arduino.h"
#include "AnalogReader.h"

AnalogReader::AnalogReader(int16_t outputRangeMin, int16_t outputRangeMax, uint16_t recentValuesAmount, uint8_t pin, uint16_t readMin, uint16_t readMax)
{
  _readMin = readMin;
  _readMax = readMax; 
  _outputRangeMin = outputRangeMin;
  _outputRangeMax = outputRangeMax;
  _noiseThreshold = (readMax - readMin) / (outputRangeMax - outputRangeMin) - 1;
  _recentValuesAmount = recentValuesAmount;
  _pin = pin;
}


uint16_t AnalogReader::getCurrentValueRaw()
{
  return _currentValue;
}

int16_t AnalogReader::getCurrentValue()
{

  return map(_currentValue, _readMin, _readMax, _outputRangeMin, _outputRangeMax);
}


void AnalogReader::setOutputRange(int16_t rangeMin, int16_t rangeMax)
{
  _outputRangeMin = rangeMin;
  _outputRangeMax = rangeMax;
  _noiseThreshold = (_readMax - _readMin) / (_outputRangeMax - _outputRangeMin);
}


int16_t AnalogReader::getOutputRangeMin()
{
  return _outputRangeMin;
}

int16_t AnalogReader::getOutputRangeMax()
{
  return _outputRangeMax;
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

