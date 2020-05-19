/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 21.01.2018 15:19:48
 Libraries   :
 Author      :
 Description :
******************************************************************/
      
      // Make a Kernel Control Structure Here     
      KernelControlStruct KernelControl;

      // Now make some Tasks for this Core - these are the data structures that define a task.
      SysTask RedFlash;                // Hullo World Task - must be disabled in normal use 
      SysTask Buttons;                 // Respond to button state 
      SysTask Lights;                  // Update lights     
      SysTask GSICalc;                 // Process ADC readings and update GSI value 
      SysTask InsideOut;               // Diagnostic Task to output data to the LED pins - when used RedFlash and TickTock should be disabled.  This task must be disabled in normal use

      // Array of task pointers
      SysTask* TaskPointers[] {
              &RedFlash,
              &Buttons,                  
              &Lights,                      
              &GSICalc,                 
              &InsideOut,               
              
              &NullTask                // This pointer must be the last in the list
              };
            
      // !!! ADD WDT Save and Restore pointers in TaskStateSaver
              
