/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.11.2016 17:06:47
 Libraries   :
 Author      :
 Description :
******************************************************************/

void RedInit (SysTask* TaskDataBlock) {
    
    // Hardware in initialised during environment build

    // Override default values
    // Initialise task priorities
    TaskDataBlock->TaskPriority = 0;

    // Initialise GPIO
    // See HardwareInit.  LEDs are used during startup

    // Recover State from NVS - defaults to RedFlashDefaultRate
    RestoreStateRedFlashonWDT();
    
    // Kick off the task that will make it flash
    RunTask (TaskDataBlock);

    return;
    };

    
void RunRedFlash (SysTask* TaskDataBlock) {

    // Record the actual start time and latency
    TaskStartingNow(TaskDataBlock);

    // Toggle Red LED
    KernelControl.RedLEDState = !KernelControl.RedLEDState;
    if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
 
    // Toggle Green LED
    KernelControl.GreenLEDState = !KernelControl.GreenLEDState;
    if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);     
    
    //TickTockCore1Control.OutputState = !TickTockCore1Control.OutputState;
    //digitalWrite(TickTockPinCore1, TickTockCore1Control.OutputState); 
    
    //TaskDataBlock = WaitTask(TaskDataBlock, KernelControl.FlashRate);  //Wait this task 
    WaitTask(TaskDataBlock, KernelControl.FlashRate);  //Wait this task 
    // Overwrite wait if Self check error detected
    if (KernelControl.SelfCheckError != 0) WaitTask(TaskDataBlock, 80);  //Wait this task 
    return;
    };

