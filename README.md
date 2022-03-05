This library helps to filter noise, from analog input (for example from potenciometer input).

Functions:
```js
// Creates instance of analog reader
AnalogReader(
   int16_t outputRangeMin, // determines minimal output value
   int16_t outputRangeMax, // determines maximal output value
   uint16_t recentValuesAmount, // how many values from previous reads should be held to calculate avreage (the bigger the value, the better noise filtering, but the slower reaction to change) 
   uint8_t pin, // pin to read from
   uint16_t readMin, // minimal value analog can provide
   uint16_t readMax // maximal value analog can provide
   );
```
```js
// get current value not mapped to outputRangeMin;outputRangeMax
uint16_t getCurrentValueRaw();
```
```js
// get current value mapped to outputRangeMin;outputRangeMax
int16_t getCurrentValue();
```
```js
// sets output range
void setOutputRange(
   int16_t rangeMin, 
   int16_t rangeMax
   );
```
```js
int16_t getOutputRangeMax();
```
```js
int16_t getOutputRangeMin();
```
```js
// this function updates analog reader values, and should get called as often as possible
// returns true, if mapped value got changed
boolean update();
```
```js
// sets pin to read analog input from
void setPin(
   uint8_t pin
   );
```




Code example: 
```js
#include <AnalogReader.h>


// create analog reader that maps analog read value to -50;50 (inclusive)
// 6 is the number of of saved values -> average is calculated from those values, to prevent voltage spikes from changing the output
// the bigger the number, the slower the change, and better noise filtering
// potenciometer is connected to pin 0
// 50;1000 (inclusive) are max and min values, that can be read from my poteciometer (every time), when connected to my circuit
AnalogReader analogReader(-50,50,6,0,50,1000);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // change the ouput range from -50;50 to 0;50 after 15 seconds
  if(millis() == 15000)
  {
    analogReader.setOutputRange(0,50);
  }

  // print current mapped value from potenciometer, if it has been changed this update
  if(analogReader.update())
  {
    Serial.println(analogReader.getCurrentValue());
  }
}
```
