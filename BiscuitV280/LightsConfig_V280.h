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

// Delay before Lights task starts (mS)
const int32_t LightsStartmS = 1000;

// Lights task normal run rate (mS)
const int32_t LightsRunRatemS = 400;

// This is the count below the target GSI that the RED LED goes on
const int16_t LightsRedCountBelowGSI = 40;

// This is the count above the target GSI that the Green LED goes on
const int16_t LightsGreenCountAboveGSI = 1;
