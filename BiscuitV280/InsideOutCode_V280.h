/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.11.2016 17:06:47
 Libraries   :
 Author      :
 Description :
******************************************************************/
/*
Reference:


*/

void InitInsideOut (SysTask* TaskDataBlock) {

    // Override default values
    // Initialise task priorities
    TaskDataBlock->TaskPriority = 0;

    // Recover InsideOut State from NVS - may overwrite some of the above
    // Standard NVS Restore
    LoadInsideOutfromNVS();    
    
    // If WDT restart recover pre WDT InsideOut State from NVS - may overwrite some of the above    
    RestoreStateInsideOut();
    
    // Kick Off the Main Task
    // TaskDataBlock = RunTask (TaskDataBlock);
    WaitTask(TaskDataBlock, InsideOutStartmS);  //Wait this task  ;        
    
    return;
    };


// This code blocks!  It is intended for diagnostic use only
// The task sends 16 bits of data to the LED pins every second
// It is intended to be used with a logic analyser that captures the data.
// Can coexist with the LED flash task, but it is easier to use if the flash task is stopped.
    
void RunInsideOut (SysTask* TaskDataBlock) {

      int16_t localStore;
      int localidx;

      // Record the actual start time and latency
      TaskStartingNow(TaskDataBlock);

      // Get data to be output to local store (in case it changes)
      // localStore = GSICalcData.GSIInput;     // Diagnostic code
      localStore = GSICalcData.GSITarget;        
      // localStore = 0xFAF5;                   // Diagnostic code
      
      // Send 3 "start" bits
      localidx = 0;
      while (localidx<3) {
      
            // Set Led pins off
            KernelControl.RedLEDState = false;
            if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
            KernelControl.GreenLEDState = false;
            if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);              
            delay(InsideOutBitLengthmS);
            // Set LED pins on
            KernelControl.RedLEDState = true;
            if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);            
            KernelControl.GreenLEDState = true;
            if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);
            delay(InsideOutBitLengthmS);             
            // Do it again  
            localidx=localidx+1;
            }

      // Hold both pins low      
      KernelControl.RedLEDState = false;
      if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
      KernelControl.GreenLEDState = false;
      if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);      
      delay(InsideOutBitLengthmS);        
            
      // Output from big end so it is the right way round on the logic analyser
      localidx = 0;
      while (localidx<16) {
            // Data in on the Red LED Pin
            KernelControl.RedLEDState = bitRead(localStore,15);
            localStore = localStore<<1;
            if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
            delayMicroseconds(25);            
            // Green LED pin toggles to create a clock of sorts.
            KernelControl.GreenLEDState = !KernelControl.GreenLEDState;
            if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);
            delay(InsideOutBitLengthmS);
            
            localidx=localidx+1;
            }

      // Hold both pins low again     
      KernelControl.RedLEDState = false;
      if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
      KernelControl.GreenLEDState = false;
      delay(InsideOutBitLengthmS);            
            
      // Wait until next time  
      WaitTask(TaskDataBlock, InsideOutRunRatemS);        // Delay if not printing - determines normal run rate

      return;
      };

