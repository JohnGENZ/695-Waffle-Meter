/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 21.01.2018 14:35:59
 Libraries   :
 Author      :
 Description :
******************************************************************/

void BiscuitKernel_V280Init() {

      String localString;
      SysTask* localTaskPtr;
      int32_t localCount;      

      // Disable wdt during setup
      wdt_disable();

      // Load Constants from NV Storage (EEProm in the old money)
      LoadMachineState();      
      
      // Set up hardware  
      HardwareInit();      
      
      // Setup is protected from interrupts (delay() will not work)
      noInterrupts();
      
      // Reset Self Check Error Flag
      KernelControl.SelfCheckError=0;

      // Setup Biscuit watchdog
      KernelControl.KernelWatchDogTimer = 0;
      KernelControl.WatchDogOverRide = false;  
      
      // Clear system lock bits for all tasks before hardware config
      ClearSystemLocks();      
      
      // Lock or unlock tasks here
      // To properly share the LEDs, only one of RedFlash, Lights, or InsideOut should be unlocked
      // In normal use Lights is unlocked and RedFlash and InsideOut are locked  
      RedFlash.Lockit = true;                 // Sends heartbeat to LEDs
      Buttons.Lockit = false;                 // Respond to button state 
      Lights.Lockit = false;                  // Update lights     
      GSICalc.Lockit = false;                 // Process ADC readings and update GSI value 
      InsideOut.Lockit = true;                // Diagnostic Task to output data to the LED pins.  This task blocks and must be locked off in normal use
      

      // Set Number of Tasks
      KernelControl.NumberOfTasksV4 = 0;

      if (TestLock(&RedFlash)==false) NewSysTask(&RedFlash, 1);
      if (TestLock(&RedFlash)==false) RedInit(&RedFlash);
      KernelControl.NumberOfTasksV4 = KernelControl.NumberOfTasksV4+1;
     
      if (TestLock(&Buttons)==false) NewSysTask(&Buttons, 2);
      if (TestLock(&Buttons)==false) InitButtons(&Buttons);
      KernelControl.NumberOfTasksV4 = KernelControl.NumberOfTasksV4+1;
      
      if (TestLock(&Lights)==false) NewSysTask(&Lights, 3);
      if (TestLock(&Lights)==false) InitLights(&Lights);
      KernelControl.NumberOfTasksV4 = KernelControl.NumberOfTasksV4+1;

      if (TestLock(&GSICalc)==false) NewSysTask(&GSICalc, 4);
      if (TestLock(&GSICalc)==false) InitGSICalc(&GSICalc);
      KernelControl.NumberOfTasksV4 = KernelControl.NumberOfTasksV4+1;

      if (TestLock(&InsideOut)==false) NewSysTask(&InsideOut, 5);
      if (TestLock(&InsideOut)==false) InitInsideOut(&InsideOut);
      KernelControl.NumberOfTasksV4 = KernelControl.NumberOfTasksV4+1;      
      
      // Set timer 1 to interrupt every say 250uS and point it at HeartBeatProcess, https://www.pjrc.com/teensy/td_libs_TimerOne.html, https://github.com/PaulStoffregen/TimerOne
      Timer1.initialize(HeartBeatPerioduS);
      Timer1.attachInterrupt(HeartBeatProcess);
      
      // Restore Task States
      // Some things may only be reloaded on a WDT restart
      // RestoreTaskStates();  

      // Ready to rock and roll - enable interrupts
      interrupts();
      // and enable WDT.  Kernel WDT should normally trigger first (see WatchDogCount in BiscuitKernelConfig)
      wdt_enable(WDTO_8S);    // https://www.nongnu.org/avr-libc/user-manual/group__avr__watchdog.html    
 
      // Sign on by flashing the lights
      SignalStart();
      
      }


void BiscuitKernel_V280() {

      while (true) {

            // Loop for all max priority tasks (say =3), then all 2&3, then all 1,2&3 tasks    
            for (KernelControl.PriorityToRun=MaxPriorityTested; KernelControl.PriorityToRun>=0; KernelControl.PriorityToRun--) {

                 // Set flags here for each task - these will set run request if time to run it
                 ProcessTaskFlags(&RedFlash);
                 ProcessTaskFlags(&Buttons);
                 ProcessTaskFlags(&Lights);
                 ProcessTaskFlags(&GSICalc);
                 ProcessTaskFlags(&InsideOut);                 
                 
                 KernelControl.NextTaskToRunOnThisCore = 1;
                 while (KernelControl.NextTaskToRunOnThisCore <= KernelControl.NumberOfTasksV4) {   

                     // If the Run flag is set, run it here.
                     switch(KernelControl.NextTaskToRunOnThisCore) {
                           case 1:
                               { 
                               if ((TaskReady(&RedFlash) == true) && (RedFlash.TaskPriority >= KernelControl.PriorityToRun)) {
                                     RunRedFlash (&RedFlash);
                                     TaskDone (&RedFlash);
                                     };
                               break;
                               }
                               
                           case 2:
                               { 
                               if ((TaskReady(&Buttons) == true) && (Buttons.TaskPriority >= KernelControl.PriorityToRun)) {
                                     RunButtons (&Buttons);
                                     TaskDone (&Buttons);
                                     };
                               break;
                               } 

                           case 3:
                               { 
                               if ((TaskReady(&Lights) == true) && (Lights.TaskPriority >= KernelControl.PriorityToRun)) {
                                     RunLights (&Lights);
                                     TaskDone (&Lights);
                                     };
                               break;
                               } 

                           case 4:
                               { 
                               if ((TaskReady(&GSICalc) == true) && (GSICalc.TaskPriority >= KernelControl.PriorityToRun)) {
                                     RunGSICalc (&GSICalc);
                                     TaskDone (&GSICalc);
                                     };
                               break;
                               } 

                           case 5:
                               { 
                               if ((TaskReady(&InsideOut) == true) && (InsideOut.TaskPriority >= KernelControl.PriorityToRun)) {
                                     RunInsideOut (&InsideOut);
                                     TaskDone (&InsideOut);
                                     };
                               break;
                               }                                

                           default:
                               {  
                               
                               };
                    
                          };
                     
                     
                     // Reset Watchdog Timer if count less than 50000 - a WDT reboot can be forced by setting the count greater than 49999
                     if(KernelControl.KernelWatchDogTimer<50000) KernelControl.KernelWatchDogTimer = 0;     // Feed the big dog 
                     // Feed the Watchdog
                     wdt_reset();                                                                           // Feed the little dog  
                     
                     KernelControl.NextTaskToRunOnThisCore = KernelControl.NextTaskToRunOnThisCore + 1;
                     
                     }  
                     
                 }     

            }
      }


