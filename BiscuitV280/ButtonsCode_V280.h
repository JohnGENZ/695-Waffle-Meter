/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 15.11.2016 17:06:47
 Libraries   :
 Author      :
 Description :
******************************************************************/
/*
Reference:


*/

void InitButtons (SysTask* TaskDataBlock) {

    // Override default values
    // Initialise task priorities
    TaskDataBlock->TaskPriority = 0;

    // Recover Button State from NVS - may overwrite some of the above
    // Standard NVS Restore
    LoadButtonsfromNVS();    
    
    // If WDT restart recover pre WDT Button State from NVS - may overwrite some of the above    
    RestoreStateButtons();

    // Initialise GPIO
    pinMode(SET_Switch, INPUT_PULLUP);
    pinMode(PTT_Switch, INPUT_PULLUP);

    // Initialse internal values
    ButtonsData.SET_SwitchState = -1;          // Switch 0 state.  1 = open, 0 = closed, -1 = don't know
    ButtonsData.PTT_SwitchState = -1;          // Switch 1 state.  1 = open, 0 = closed, -1 = don't know
    
    // Kick Off the Main Task
    // TaskDataBlock = RunTask (TaskDataBlock);
    WaitTask(TaskDataBlock, ButtonsStartmS);  //Wait this task  ;        
    
    return;
    };

    
void RunButtons (SysTask* TaskDataBlock) {

      int localNewState;

      // Record the actual start time and latency
      TaskStartingNow(TaskDataBlock);

      // Check SET_Switch
      localNewState = ReadSwitch (SET_Switch);
      // See if there is a change - -1 means state not known and is ignored
      if ((localNewState != -1) && (localNewState != ButtonsData.SET_SwitchState)) {
            if ((localNewState == 0) && (ButtonsData.SET_SwitchState != -1)) SET_Switch_Closed();    // Do this if the new state is switch closed and button state is known (ie not = -1 on first scan)
            if ((localNewState == 1) && (ButtonsData.SET_SwitchState != -1)) SET_Switch_Open();      // Do this if the new state is switch open  and button state is known (ie not = -1 on first scan)
            ButtonsData.SET_SwitchState = localNewState;            
            }

      // Check PTT_Switch
      localNewState = ReadSwitch (PTT_Switch);
      // See if there is a change - -1 means state not known and is ignored
      if ((localNewState != -1) && (localNewState != ButtonsData.PTT_SwitchState)) {
            if ((localNewState == 0) && (ButtonsData.PTT_SwitchState != -1)) PTT_Switch_Closed();    // Do this if the new state is switch closed and button state is known (ie not = -1 on first scan)
            if ((localNewState == 1) && (ButtonsData.PTT_SwitchState != -1)) PTT_Switch_Open();      // Do this if the new state is switch open  and button state is known (ie not = -1 on first scan)
            ButtonsData.PTT_SwitchState = localNewState;            
            }

      WaitTask(TaskDataBlock, ButtonsRunRatemS);        // Delay if not printing - determines normal run rate

      return;
      };

