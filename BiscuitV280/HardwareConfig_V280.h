/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 21.01.2018 15:08:53
 Libraries   :
 Author      :
 Description :
******************************************************************/

//  Definitions to match the ATTINY physical pins to the Arduino Core logical pins
#define ATTINYPhysicalPin2  3      // Physical Pin2
#define ATTINYPhysicalPin3  4      // Physical Pin3 
#define ATTINYPhysicalPin5  0      // Physical Pin5 
#define ATTINYPhysicalPin6  1      // Physical Pin6
#define ATTINYPhysicalPin7  2      // Physical Pin7


// LED Pins
const int RedLEDPin = ATTINYPhysicalPin5;    // PB0
const int GreenLEDPin = ATTINYPhysicalPin6;  // PB1

// ADC In
const int Voice_ADC = A1;    // ADC1

// Digital Inputs
const int SET_Switch = ATTINYPhysicalPin2;      // PB3, also reserved for RX
const int Soft_RX = ATTINYPhysicalPin2;         // PB3, also reserved for SET_Switch
const int PTT_Switch = ATTINYPhysicalPin3;      // PB4, also reserved for TX
const int Soft_TX = ATTINYPhysicalPin3;         // PB4, also reserved for PTT_Switch
 
// Define TickTock Pin.  If Pin# = -1 then pin is not initialised and TickTock task is Locked off.
const int TickTockPin = -1;  // PH5

// --------------------------------------------
// EEPROM Allocation
const int8_t HW_WDTResetCount = 100;        // int32_t
const int8_t RedRateNVS = 104;              // int32_t    
const int8_t Kernel_WDTNVS = 108;           // int32_t   
const int8_t startcounterNVS = 112;         // int32_t
const int8_t NVS_VersionNVS = 116;          // int32_t
const int8_t GSITargetNVS = 120;            // int16_t 
const int8_t WDT_DID_IT_NVS  = 124;         // bool
 //128




