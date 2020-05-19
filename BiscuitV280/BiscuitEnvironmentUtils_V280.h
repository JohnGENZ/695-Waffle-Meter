/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 21.01.2018 13:25:30
 Libraries   :
 Author      :
 Description :
******************************************************************/

// Utilities Used to build the hardware environment


void(* resetFunc) (void) = 0x0;   //declare reset function at address 0 


void ClearNVS() {
      for (int32_t i=0;i<TopOfEEPROM; i++) EEPROM.write(i, 0);

      }

      
void LoadFactoryConfig() {
      // Reload the factory configuration here 
      int32_t tempint32;

      ClearNVS();
      
      // Reset WDT counts
      tempint32 = 0;
      // Kernel
      EEProm_put_int32_t(Kernel_WDTNVS, tempint32);

      // Reset restart flag if needed and save it      
      EnvironmentControl.SystemRestartedbyWDT = false;
      EEProm_put_Bool(WDT_DID_IT_NVS, EnvironmentControl.SystemRestartedbyWDT);                   

      // Feed the Watchdog
      wdt_reset();

      // Load task data to NVS - must reopen CoreXNVS
      LoadFactoryConfigGSICalctoNVS();
      
      }

