/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 11.04.2017 09:23:52
 Libraries   :
 Author      :
 Description :
******************************************************************/
/*
Reference:


*/

// Load Variables from NVS - usually called on startup
void LoadGSICalcfromNVS() {
      // Load NVS
      GSICalcData.GSITarget = EEProm_get_int16_t (GSITargetNVS);
      }

// Store Variables to NVS - may be called when a variable is changed
void StoreGSICalcToNVS() {
      // NVS MUST be open

      }      

// Load Factory Config - called from BiscuitEnvironment Utils
void LoadFactoryConfigGSICalctoNVS() {
      // Set NVS Variables here
      EEProm_put_int16_t(GSITargetNVS, GSITargetFactoryConfig);

      // Load NVS
      GSICalcData.GSITarget = EEProm_get_int16_t (GSITargetNVS);
      }      
      

// To use these add WDT Save and Restore pointers in TaskStateSaveCore1 or 2
void SaveStateGSICalc() {
      // Save GSICalc state on WDT restart
      
      }

void RestoreStateGSICalc() {
      // Restore GSICalc state after WDT restart
      if(EnvironmentControl.RestartingAfterWDT==true) {
            
            }  

      }
  
