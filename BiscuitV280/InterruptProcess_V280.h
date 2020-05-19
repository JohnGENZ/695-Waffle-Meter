/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 23.01.2018 10:49:25
 Libraries   :
 Author      :
 Description :
 
 https://esp-idf.readthedocs.io/en/v2.0/general-notes.html#iram-instruction-ram
 
******************************************************************/

// Respond to Heartbeat Here
void HeartBeatProcess() {

        // Toggle Green LED - diagnostic code for timing ISR
        // KernelControl.GreenLEDState = !KernelControl.GreenLEDState;
        // digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);

        // Sample ADC
        GSICalcData.ADCReading[GSICalcControl.ADCReadingIndex]= analogRead(Voice_ADC);   
        GSICalcControl.ADCReadingIndex = GSICalcControl.ADCReadingIndex+1;  
        if (GSICalcControl.ADCReadingIndex>=ADCBufferSize) GSICalcControl.ADCReadingIndex = 0;

        // Trigger processing task
        RunTask (&GSICalc);

        // Return if WDT suspended
        if (KernelControl.WatchDogOverRide==true) return;
        
        KernelControl.KernelWatchDogTimer = KernelControl.KernelWatchDogTimer+1;
        if (KernelControl.KernelWatchDogTimer > WatchDogCount) {
            
            // Turn off power
            // digitalWrite(ToasterPopUpRelay, POWEROFF);
            
            // trigger WDT reset
            KernelControl.HowManyTimes = EEProm_get_int32_t(Kernel_WDTNVS);
            KernelControl.HowManyTimes = KernelControl.HowManyTimes + 1;

            
            // Indicate this is a WDT restart
            EnvironmentControl.SystemRestartedbyWDT = true;           

            // write new count and reset
            EEProm_put_int32_t(Kernel_WDTNVS, KernelControl.HowManyTimes);            
            
            // Save System State
            SaveMachineState();
            
            // Save Task States
            SaveTaskStates();
            
            resetFunc();      //call reset
            while(true) {};   // Should never get here  
            };
            
        // Toggle Green LED - diagnostic code
        // KernelControl.GreenLEDState = !KernelControl.GreenLEDState;
        // digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);            
            
            
       }; 

