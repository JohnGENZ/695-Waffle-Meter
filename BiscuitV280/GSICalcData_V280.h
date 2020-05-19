/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 20.06.2017 11:25:44
 Libraries   :
 Author      :
 Description :
******************************************************************/
/*
Reference:


*/


      // GSICalc Control Structure 
      struct GSICalcControlStruct {
            volatile int ADCReadingIndex;               // Write index into ADC Reading Array

            };
            
      GSICalcControlStruct GSICalcControl;

      // GSICalc Data Structure 
      struct GSICalcDataStruct {
            volatile int16_t GSITarget;                      // The GSI value we want to exceed 
            volatile int16_t GSIInput;                       // Most of GSI calc    
            volatile int ADCReading[ADCBufferSize];          // Readings from the ADC are stored here on the interrupt level for processing by GSICalc

            };
            
      GSICalcDataStruct GSICalcData;
      
 


