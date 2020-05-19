/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 20.01.2018 16:07:21
 Libraries   :
 Author      :
 Description :
******************************************************************/

void CheckForNVSUpdate_V280() {

      // Check if NVS needs to be initialised from compile time values (usually a new chip)
      if(CheckNVSVersion==true) {
      
            // Get NVS Version number  
            // Load current version from NVS  
            EnvironmentControl.NVSVersion = EEProm_get_int32_t(NVS_VersionNVS);
            // Save The build version as the actual version
            EEProm_put_int32_t(NVS_VersionNVS, NVSVersionThisBuild);
            
            // If the versions do not match do an update
            if (NVSVersionThisBuild != EnvironmentControl.NVSVersion) LoadFactoryConfig();
            
            }
      }      
      
      
void BiscuitNVSLoad_V280() {

      
      }  


      // Set up NVS
void ManageNVS_V280() {
      
      // Check if NVS needs to be initialised from compile time values (usually a new chip)
      CheckForNVSUpdate_V280();
      
      // First load of NVS. NVS may also accessed as the kernel starts, and as the tasks are initialsed
      BiscuitNVSLoad_V280();      
      
      }
            
