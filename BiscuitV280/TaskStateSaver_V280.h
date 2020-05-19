/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 14.07.2018 17:14:27
 Libraries   :
 Author      :
 Description :
 
 Reference:
 Function Pointers
  https://barrgroup.com/Embedded-Systems/How-To/C-Function-Pointers
  https://www.cprogramming.com/tutorial/function-pointers.html
 
******************************************************************/

void TableEntryFault() {
 
      }

// Function pointers to save state on WDT
void (*TaskWDTSaverTable[])(void) = {
      SaveStateRedFlashonWDT,               // Red State Save
      TableEntryFault};                     // Last Entry MUST be TableEntryFault


// Function pointers to restore state after WDT 
void (*TaskWDTRestoreTable[])(void) = {
      RestoreStateRedFlashonWDT,            // Red State Restore
      TableEntryFault};                     // Last Entry MUST be TableEntryFault 


// Load Nominated State Variables from EEPROM      
void LoadMachineState () {

      // Get the counter value, if the key does not exist, return a default value of 0
      // Note: Key name is limited to 15 chars.
      EnvironmentControl.Startcounter = EEProm_get_int32_t(startcounterNVS);

      // Increase counter by 1
      EnvironmentControl.Startcounter++;
      // Save for Logging
      // MasterLoggerControl.StartCounter = EnvironmentControl.Startcounter;
      // Store the counter to the Preferences
      EEProm_put_int32_t(startcounterNVS, EnvironmentControl.Startcounter);      
      
      // Load WDT restart flag
      EnvironmentControl.SystemRestartedbyWDT = EEProm_get_Bool(WDT_DID_IT_NVS);
      EnvironmentControl.RestartingAfterWDT = EnvironmentControl.SystemRestartedbyWDT;
      
      // Reset restart flag if needed and save it
      EnvironmentControl.SystemRestartedbyWDT = false;
      EEProm_put_Bool(WDT_DID_IT_NVS, EnvironmentControl.SystemRestartedbyWDT);      
      
      }

      
// Save Nominated State Variables from EEPROM       
void SaveMachineState () {

      // Save state of WDT reset flag
      EEProm_put_Bool(WDT_DID_IT_NVS, EnvironmentControl.SystemRestartedbyWDT);       

      }    


void SaveTaskStates () {

      int32_t localArraySize;
      int32_t localCounter;
      
      localArraySize = (sizeof(TaskWDTSaverTable)/sizeof(TaskWDTSaverTable[0]))-1;
      localCounter = 0;
      
      // Save State of Tasks here
      while (localCounter<localArraySize) {
          TaskWDTSaverTable[localCounter]();
          localCounter=localCounter+1;          
          }  
      
      }


/*
void(* resetFunc) (void) = 0;   //declare reset function at address 0, https://www.instructables.com/id/two-ways-to-reset-arduino-in-software/ 

          resetFunc();      //call reset

*/
