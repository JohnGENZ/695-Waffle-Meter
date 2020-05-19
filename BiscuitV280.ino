// Include Master Build Control File Here
// Files in this build are controlled in that file

#include "MasterBuildControlFile_V280.h"

// ******************************************************************************************************************
// The real work starts here    
    
// Set up Code      
void setup() {

      // Set up NVS (ie EEPROM)
      ManageNVS_V280();

      // Initialse the Kernel      
      BiscuitKernel_V280Init();
      
      }

      
void loop() {

      // Run the Kernel forever in this version    
      BiscuitKernel_V280();
            
      };   

// Real work ends here
// **************************************************************************************************

