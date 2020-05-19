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
void LoadButtonsfromNVS() {
      // NVS MUST be open

      }

// Store Variables to NVS - may be called when a variable is changed
void StoreButtonsToNVS() {
      // NVS MUST be open

      }      

// Load Factory Config - called from BiscuitEnvironment Utils
void LoadFactoryConfigButtonstoNVS() {
      // Set NVS Variables here
      
      }      
      

// To use these add WDT Save and Restore pointers in TaskStateSaveCore1 or 2
void SaveStateButtons() {
      // Save Buttons state on WDT restart

      
      }

void RestoreStateButtons() {
      // Restore Buttons state after WDT restart
      if(EnvironmentControl.RestartingAfterWDT==true) {

            }  

      }
  
      
int ReadSwitch (int SwitchToRead) {

      int localOpenCount;
      int localClosedCount;
      int localRead;
      int localCounter;

      // Read each pin configured number (say 3) times.  State must be the same for all the reads or else the read is ignored
      // If pin is low (switch closed) return 0, if pin is high (switch open) return 1

      // Initialise counts
      localOpenCount = 0;
      localClosedCount = 0;      
      
      // Read switch the specified number of times
      localCounter = 0;
      while (localCounter<ButtonsReadCount) {
            localRead = digitalRead(SwitchToRead);     
            if(localRead == HIGH) localOpenCount = localOpenCount+1;
            if(localRead == LOW)  localClosedCount = localClosedCount+1;
            localCounter = localCounter+1;
            }

      // if it was open return 1      
      if (localOpenCount==ButtonsReadCount) return 1;
      // if it was closed return 0      
      if (localClosedCount==ButtonsReadCount) return 0;      
      // Otherwise return don't know
      return -1;
      }
      

// Do this if the new state of Switch0 is Switch0 closed 
void SET_Switch_Closed() {

      int localidx;

      // Clear (Reset) Sample Buffer
      // Protected from interrupts so it is fully cleared before it starts to fill again.
      // https://www.nongnu.org/avr-libc/user-manual/group__util__atomic.html
      localidx = 0;      
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {      
            while (localidx<ADCBufferSize) {
                  GSICalcData.ADCReading[localidx] = GSICentrePoint;
                  localidx=localidx+1;
                  }
            GSICalcControl.ADCReadingIndex = 0;      
            } 

      // Set LED states to off, will be toggled  on and off by lights      
      KernelControl.RedLEDState = false;
      KernelControl.GreenLEDState = false;
            
      // Trigger Lights Update
      RunTask (&Lights);       
      }

      
// Do this if the new state of Switch0 is Switch0 open 
void SET_Switch_Open() {
      // Capture Contents of sample buffer
      GSICalcData.GSITarget = GSICalcData.GSIInput;
       
      // Store to  NVS
      EEProm_put_int16_t(GSITargetNVS, GSICalcData.GSITarget);      

      // Trigger Lights Update
      RunTask (&Lights);      
      } 

      
// Do this if the new state of Switch1 is Switch1 closed 
void PTT_Switch_Closed() {

      // Trigger Lights Update
      RunTask (&Lights);
      }

      
// Do this if the new state of Switch1 is Switch1 open 
void PTT_Switch_Open() {

      // Trigger Lights Update
      RunTask (&Lights);
      } 

