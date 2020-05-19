/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.11.2016 17:06:47
 Libraries   :
 Author      :
 Description :
******************************************************************/
/*
Reference:


*/

void InitLights (SysTask* TaskDataBlock) {

    // Override default values
    // Initialise task priorities
    TaskDataBlock->TaskPriority = 0;

    // Recover Lights State from NVS - may overwrite some of the above
    // Standard NVS Restore
    LoadLightsfromNVS();    
    
    // If WDT restart recover pre WDT Lights State from NVS - may overwrite some of the above    
    RestoreStateLights();
    
    // Kick Off the Main Task
    // TaskDataBlock = RunTask (TaskDataBlock);
    WaitTask(TaskDataBlock, LightsStartmS);  //Wait this task  ;        
    
    return;
    };

    
void RunLights (SysTask* TaskDataBlock) {

#define DoNothing 1
#define OperateMode 2
#define RecordMode 3

      int localState;
      int16_t localGSIHigh;
      int16_t localGSILow;

      // Record the actual start time and latency
      TaskStartingNow(TaskDataBlock);

      // Welcome to the State Machine
      // The new state of the machine is determined by the staet of the other tasks
      // Note button state inverted - inputs are pulled low by button push
 
      /*
      // Diagnostic code - Set LED pins to button states
      KernelControl.RedLEDState = !ButtonsData.SET_SwitchState;
      if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
      KernelControl.GreenLEDState = !ButtonsData.PTT_SwitchState;
      if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);      
      */

      // Set up default
      localState = DoNothing;
    
      // PTT off, SET off, lights off, do nothing 
      if ((!ButtonsData.SET_SwitchState == false) && (!ButtonsData.PTT_SwitchState == false)) localState = DoNothing;

      // PTT off, SET on, lights off, do nothing 
      if ((!ButtonsData.SET_SwitchState == false) && (!ButtonsData.PTT_SwitchState == true)) localState = OperateMode;      
      
      // PTT on, SET off, Operate mode - indicate levels 
      if ((!ButtonsData.SET_SwitchState == true) && (!ButtonsData.PTT_SwitchState == false)) localState = RecordMode;
      
      // PTT on, SET on, Record mode, record new target GSI
      if ((!ButtonsData.SET_SwitchState == true) && (!ButtonsData.PTT_SwitchState == true)) localState = RecordMode;

      // Calculate local GSI targets
      localGSIHigh = GSICalcData.GSITarget+LightsGreenCountAboveGSI;
      if(localGSIHigh>(GSICentrePoint*GSIScaleFactor)) localGSIHigh = GSICentrePoint*GSIScaleFactor;
      localGSILow = GSICalcData.GSITarget-LightsRedCountBelowGSI;
      if(localGSILow<1) localGSILow = 1;
      
      switch (localState) {

            case DoNothing:             // Lights off, do nothing 
                  KernelControl.RedLEDState = false;
                  if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
                  KernelControl.GreenLEDState = false;
                  if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);     
                  break;
                  
            case OperateMode:           // Indicate Levels with the lights
                  // IF GSI below target less lower limit turn on red LED, turn off green
                  if(GSICalcData.GSIInput<localGSILow) {
                        KernelControl.RedLEDState = true;
                        if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState); 
                        KernelControl.GreenLEDState = false;
                        if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);                        
                        }

                  // IF GSI between lower and higher limts turn off both LEDs
                  if((GSICalcData.GSIInput>=localGSILow) && (GSICalcData.GSIInput<=localGSIHigh)) {
                        KernelControl.RedLEDState = false;
                        if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState); 
                        KernelControl.GreenLEDState = false;
                        if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);                        
                        }                        
                        
                  // IF GSI above target plus higher limit turn off red LED, turn on green
                  if(GSICalcData.GSIInput>localGSIHigh) {
                        KernelControl.RedLEDState = false;
                        if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState); 
                        KernelControl.GreenLEDState = true;
                        if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);                        
                        }
                  break;
                  
            case RecordMode:           // Record new GSI
                  // Toggle both LEDs in record mode
                  KernelControl.RedLEDState = !KernelControl.RedLEDState;
                  if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState); 
                  KernelControl.GreenLEDState = !KernelControl.GreenLEDState;
                  if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);                        
                  break;
                  
            default:
                  break;
                  
            } 
      
      // Wait until next time - normally this is the flash rate but may be run when button changes state 
      WaitTask(TaskDataBlock, LightsRunRatemS);        // Delay if not printing - determines normal run rate

      return;
      };

