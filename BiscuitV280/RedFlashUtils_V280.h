/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 11.04.2017 09:23:52
 Libraries   :
 Author      :
 Description :
******************************************************************/
/*
Reference:


*/

void SaveStateRedFlashonWDT() {

      int32_t localInt;

      // Save RedFlash state on WDT restart
      // Access Non volatile memory - https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences
      
      localInt = KernelControl.FlashRate;      
      EEProm_put_int32_t(RedRateNVS, localInt);     

      
      }

void RestoreStateRedFlashonWDT() {
      // Restore RedFlash state after WDT restart
      
      // Set default rate for normal restart
      KernelControl.FlashRate = RedFlashDefaultRate;
      // Recover last rate if restarting after WDT
      if(EnvironmentControl.RestartingAfterWDT==true) KernelControl.FlashRate = EEProm_get_int32_t(RedRateNVS);       

      }    
