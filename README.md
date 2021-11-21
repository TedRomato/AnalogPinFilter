# AnalogPinFilter
Filters noise from analog input.

<h2>How it works:</h2>
<p>
AnalogReader keeps track of recentValuesAmount amount of reads. When new read comes in array shifts to the left, and adds new value to the last index.
Average of recent values is calculated, and if average is bigger or smaller than currentValue (accesible with getCurrentValue()) +- noiseThreshold, this value is saved as currentValue.
</p>

<h2>AnalogReader constructor:</h2>
AnalogReader(uint16_t noiseThreshold, uint16_t recentValuesAmount, uint8_t pin, uint16_t readMin, uint16_t readMax)
<ul>
   <li>
       <h3>noiseThreshold</h3>
       <br>
       An absolute value, that has to be between the new average and currentValue, to set currentValue to the average.
       
   </li>
   <li>
       <h3>recentValuesAmount</h3>
       <br>
       Number of values held for average calculation.
       
   </li>
   <li>
       <h3>pin</h3>
       <br>
       Analog pin.
       
   </li>
   <li>
       <h3>readMin</h3>
       <br>
       Minimal input value, that can be consistently read from analog pin. 
       
   </li><li>
       <h3>readMax</h3>
       <br>
       Maximal input value, that can be consistently read from analog pin.
       
   </li>
</ul>

<b>Note:</b> 
readMin and readMax are used to counter for imperfect components. <br> 
<b>Example:</b>
My potenciometer should be able to provide values between 0 - 1023, but realistically its range is somwhere around 50 - 1000,<br> so I would set readMin tp 50 and readMax to 1000.
