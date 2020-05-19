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
void LoadInsideOutfromNVS() {
      // NVS MUST be open

      }

// Store Variables to NVS - may be called when a variable is changed
void StoreInsideOutToNVS() {
      // NVS MUST be open

      }      

// Load Factory Config - called from BiscuitEnvironment Utils
void LoadFactoryConfigInsideOuttoNVS() {
      // Set NVS Variables here
      
      }      
      

// To use these add WDT Save and Restore pointers in TaskStateSaveCore1 or 2
void SaveStateInsideOut() {
      // Save InsideOut state on WDT restart

      
      }

void RestoreStateInsideOut() {
      // Restore InsideOut state after WDT restart
      if(EnvironmentControl.RestartingAfterWDT==true) {
            
            }  

      }
  
