/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 22.01.2018 21:28:07
 Libraries   :
 Author      :
 Description :
******************************************************************/


//Process tasks flags here - decide to run it - but actual run code is elswhere - what gets run first has to be prioritised
void ProcessTaskFlagsNow (SysTask* TaskToCheck) {

      if (TaskToCheck->Lockit == true) return;  // Return if task locked
      if (TaskToCheck->SysLockit != 0) return;  // Task does not run if any system lock bits set      
      if (TaskToCheck->TaskPriority < 0) return;  // Return if priority negative
      if (TaskToCheck->TaskWait > 0) return;   // Return if something(s) are asking the task to wait

      if (((millis() >= TaskToCheck->WaitUntil) && (TaskToCheck->WaitUntil != 0)) || (TaskToCheck->TightLoop == true)) {
          TaskToCheck->WaitUntil=0;
          TaskToCheck->ForceWait=false;
          TaskToCheck->RunNow = true;  // Set run flag 
          //TaskToCheck->RunNowTaskTimeStamp = millis(); // Record the time we asked
      };

      return;
      };

//Lock Task table and process tasks flags here
void ProcessTaskFlags (SysTask* TaskToCheck) {

      ProcessTaskFlagsNow(TaskToCheck);
            
      return;
      };  
      
            
// Initialise a Task
void NewSysTask (SysTask* TaskToBuild, int NewTask) {
      TaskToBuild->TaskVersion = 1;
      TaskToBuild->TaskIDNum = NewTask;
      TaskToBuild->RunNow = false;
      TaskToBuild->TightLoop = false;
      TaskToBuild->ForceWait = false;
      TaskToBuild->TaskWait = 0;
      TaskToBuild->WaitUntil = 0;
      // Initialise task priorities
      TaskToBuild->TaskPriority = 0;
      return;
      };

      
// Called as a task starts to save time values
void TaskStartingNow (SysTask* TaskToStart) {
      
      return;     
      };           
      
      
// Ask a task to wait
void WaitTask (SysTask* TaskToWait, unsigned long msToWait) {
      unsigned long WorkingStore;
      WorkingStore = millis();
      TaskToWait->WaitUntil = WorkingStore + msToWait;
      // if rolls over to 0 will not run, so add 1
      if (TaskToWait->WaitUntil == 0) TaskToWait->WaitUntil = 1;
      return;
      };

      
// Run a task now
void RunTask (SysTask* TaskToRun) {

      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
             TaskToRun->RunNow = true;  // Set run flag 
            }
            
      return;
      };

      
// Returns true if task ready to go 
boolean TaskReady (SysTask* TaskToTest) {
      boolean WorkingFlag;

      if ((TaskToTest->TaskWait > 0) && (TaskToTest->ForceWait == true)) return false;
      
      WorkingFlag = false;      
      if ((TaskToTest->RunNow == true) && (TaskToTest->Lockit == false) && (TaskToTest->SysLockit == 0) && (TaskToTest->TaskWait == 0)) WorkingFlag = true;
      return WorkingFlag;
      };

      
// Lock a task
void LockTask (SysTask* TaskToLock) {
      TaskToLock->Lockit = true;  // Set run flag 
      return;
      };
    
// Unlock a task
void UnlockTask (SysTask* TaskToUnlock) {
      TaskToUnlock->Lockit = false;  // Set run flag 
      return;
      };


// Tidies up after a task has run
void TaskDone (SysTask* TaskToTidy) {

      // Reset Flags and Timestamp
      TaskToTidy->RunNow = false;

      return;
      };
      
      
// Clear the system lock bits of a task      
void ClearSystemLock(SysTask* TaskToClear) {
       TaskToClear->SysLockit = 0; 
      }

      
// This routine clears the system lock bits for all tasks
void ClearSystemLocks() {

      SysTask* localTaskPtr;
      int32_t localCount;
      
      localTaskPtr = &NullTask;
      
      localCount=0;
      while(localTaskPtr != TaskPointers[localCount]) {
            ClearSystemLock(TaskPointers[localCount]);
            localCount=localCount+1;
            }
            
      }

      
// Return true if task locked, false otherwise
boolean TestLock (SysTask* TaskToTest) {

      if(TaskToTest->Lockit == true) return true;
      if(TaskToTest->SysLockit != 0) return true; 
            
      return false;
      };         

      
// Set System Lock Bit
void SetSysLock(SysTask* TaskToLock, int32_t BitToLock) {
      
      // do nothing and return if bit invalid
      if(BitToLock>31) return;
      if(BitToLock<0) return;
      
      // Write the bit
      bitSet(TaskToLock->SysLockit, BitToLock);
      return;
      
      }
      
// UnSet System Lock Bit
void UnSetSysLock(SysTask* TaskToLock, int32_t BitToLock) {
      
      // do nothing and return if bit invalid
      if(BitToLock>31) return;
      if(BitToLock<0) return;
      
      // Write the bit
      bitClear(TaskToLock->SysLockit, BitToLock);
      return;
      
      }           

// freeMemory - see https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory   
      #ifdef __arm__
      // should use uinstd.h to define sbrk but Due causes a conflict
      extern "C" char* sbrk(int incr);
      #else  // __ARM__
      extern char *__brkval;
      #endif  // __arm__
       
      int freeMemory() {
        char top;
      #ifdef __arm__
        return &top - reinterpret_cast<char*>(sbrk(0));
      #elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
        return &top - __brkval;
      #else  // __arm__
        return __brkval ? &top - __brkval : &top - __malloc_heap_start;
      #endif  // __arm__
      }



    
