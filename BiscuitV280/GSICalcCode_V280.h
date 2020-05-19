/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.11.2016 17:06:47
 Libraries   :
 Author      :
 Description :
******************************************************************/
/*
Reference:


*/


void InitGSICalc (SysTask* TaskDataBlock) {

    // Override default values
    // Initialise task priorities
    TaskDataBlock->TaskPriority = 0;

    // Recover GSICalc State from NVS - may overwrite some of the above
    // Standard NVS Restore
    LoadGSICalcfromNVS();    
    
    // If WDT restart recover pre WDT GSICalc State from NVS - may overwrite some of the above    
    RestoreStateGSICalc();

    // Initialise Write Index here
    GSICalcControl.ADCReadingIndex = 0;
    
    // Kick Off the Main Task
    WaitTask(TaskDataBlock, GSICalcStartmS);  //Wait this task  ;        
    
    return;
    };

    
void RunGSICalc (SysTask* TaskDataBlock) {

      int localidx;
      int localADCReading;
      int localMax;

      // Record the actual start time and latency
      TaskStartingNow(TaskDataBlock);

      // Update the value of the GSI
      localMax = 0;
      // Do not count the first and last samples set by GSIClip
      localidx = GSIClip;
      while (localidx<(ADCBufferSize-GSIClip)) {

            // This 16 bit operation may be done in several pieces - it is important that the task is not interupted
            // Could also just disable and re-enable interrupts in this case.
            // https://www.nongnu.org/avr-libc/user-manual/group__util__atomic.html
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                  localADCReading = GSICalcData.ADCReading[localidx];
                  }
            // Find Max and Min
            localADCReading = localADCReading-GSICentrePoint;
            localADCReading = abs(localADCReading);
            if (localADCReading>localMax) localMax = localADCReading;
            
            localidx=localidx+1;
            }

      // Calc range (min to max) and scale
      GSICalcData.GSIInput = GSIScaleFactor*localMax;      

      /*
      // Diagnostic code
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            GSICalcData.GSIInput = GSICalcData.ADCReading[0];
            }
      */
      
      // Wait until next time  
      WaitTask(TaskDataBlock, GSICalcRunRatemS);        // Delay if not printing - determines normal run rate

      return;
      };

