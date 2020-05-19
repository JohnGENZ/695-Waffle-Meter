/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 13.08.2017 11:28:20
 Libraries   :
 Author      :
 Description :
******************************************************************/
/*
Reference:


*/

// Config Constants

// Delay before GSICalc task starts (mS)
const int GSICalcStartmS = 1000;

// GSICalc task normal run rate (mS) - normally triggered from interrupt level
const int GSICalcRunRatemS = 500;

// Size of array used to store ADC readings.  Must be power of 2
const int ADCBufferSize = 32;

// Clip this many samples from the begining and end of the GSI calc.  The ADC buffer must be at least (2*GSIClip)+1
const int16_t GSIClip = 2;

// Factory Config value of GSI target
const int16_t GSITargetFactoryConfig = 300;

// Centerpoint of ADC reading - not used in every version
const int16_t GSICentrePoint = 512;

// GSI Scale factor - used ot scale input reading - to avoid loss of precision should not be greater than 8
const int16_t GSIScaleFactor = 4;

