/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 21.01.2018 13:25:30
 Libraries   :
 Author      :
 Description :
 
 
******************************************************************/
       
       // Control Structure for Environment
       struct EnvironmentControlStruct {
             volatile int Startcounter;                    // Working store for number of starts
             volatile int NVSVersion;                      // The running version of the NVS storage
             volatile boolean SystemRestartedbyWDT;        // Set when system restarted by WDT - reset on restart
             volatile boolean RestartingAfterWDT;          // On restart after WDT this flag carries the state of SystemRestartedbyWDT after SystemRestartedbyWDT is reset
              
             };
       // Now make it      
       EnvironmentControlStruct EnvironmentControl;      
        
      // Define Control Structure for Kernel - built in Kernel namespace
      struct KernelControlStruct {
            volatile int NumberOfTasksV4;           // The number of tasks
            boolean RedLEDState;                    // The state of the Red monitoring LED
            boolean GreenLEDState;                  // The state of the Green monitoring LED            
            volatile uint32_t SelfCheckError;       // Self check error flag = 0 if all OK
            volatile unsigned long FlashRate;       // Use system control structure for indicator LED flash rate
            volatile uint32_t KernelWatchDogTimer;  // WatchDog Timer Storage
            volatile boolean WatchDogOverRide;      // Normally false, set true to suspend Kernel WDT     
            volatile int PriorityToRun;             // Next Priority to search Tasktable for 
            volatile int HowManyTimes;              // Count of number of times between WDT feeds 
            volatile int NextTaskToRunOnThisCore;   // Index to the next task to run on this core
            };      

            
      // Define a task structure here - built in Kernel Name space
      struct SysTask {
            //
            int SysTaskTableVersion = 280;        // Identify the version of this table
            volatile int TaskPriority;            // Priority of task a negative number means don't run
            volatile boolean RunNow;              // True When ready to run
            volatile boolean Lockit;              // Won't run while this is set - likely to be a user request
            volatile uint32_t SysLockit;          // A set of lock bits - all must be zero for task to run - likely to be set by one system task locking another
            volatile boolean TightLoop;           // Set true if must run every loop - false otherwise
            volatile unsigned long TaskWait;      // Won't run if this is >0 - likely to be waiting for other tasks
            volatile unsigned long WaitUntil;     // Will Run when millis() > WaitUntil.  WaitUntil is then Reset
            volatile boolean ForceWait;           // If ForceWait is true Wait MUST time out, if false a RUN request will be honoured immediately
            // Task Identification number and task version number
            volatile int TaskIDNum;
            volatile int TaskVersion;
             };      

      SysTask NullTask;       // Real Tasks are set up in BiscuitKernel      

