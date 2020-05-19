/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 21.03.2018 12:52:34
 Libraries   :
 Author      :
 Description :
******************************************************************/

void HardwareInit() {

      int localInt;

      // General Digital inputs
      pinMode(SET_Switch, INPUT_PULLUP);  
      pinMode(PTT_Switch, INPUT_PULLUP);  
      
      // Task specific GPIO initialised in task module init code unless required during startup
      
      // Initialise GPIO
      if(RedLEDPin != -1) {
            pinMode(RedLEDPin, OUTPUT);
            KernelControl.RedLEDState = false;
            digitalWrite(RedLEDPin, KernelControl.RedLEDState);
            } 
      if(GreenLEDPin != -1) {
            pinMode(GreenLEDPin, OUTPUT);
            KernelControl.GreenLEDState = false;
            digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);
            }    
      
      }


// --------------------------------------------------------------------------------------------------
// These routines use delay and MUST NOT be used once the kernel is running      
      
void ToggleRedAndGreen () {

      // Toggle Red LED
      KernelControl.RedLEDState = !KernelControl.RedLEDState;
      if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
      // Toggle Green LED
      KernelControl.GreenLEDState = !KernelControl.GreenLEDState;
      if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);     

      }
      
void FlashRedAndGreen () {

      // Set Red LED on
      KernelControl.RedLEDState = true;
      if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
      // Set Green LED On
      KernelControl.GreenLEDState = true;
      if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);     

      delay(FlashTimemS);
      
       // Set Red LED off
      KernelControl.RedLEDState = false;
      if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
      // Set Green LED off
      KernelControl.GreenLEDState = false;
      if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);        
      
      }      
      
void SignalStart() {

       // Set Both LEDs Off
      KernelControl.RedLEDState = false;
      if(RedLEDPin != -1) digitalWrite(RedLEDPin, KernelControl.RedLEDState);
      KernelControl.GreenLEDState = false;
      if(GreenLEDPin != -1) digitalWrite(GreenLEDPin, KernelControl.GreenLEDState);  
      
      // Three flashes  
      FlashRedAndGreen();
      delay(FlashTimemS);
      FlashRedAndGreen();
      delay(FlashTimemS);
      FlashRedAndGreen();
      delay(LongFlashTimemS);       

      // LEDs are off but leave with internal states ready for toggle  
      KernelControl.RedLEDState = false;
      KernelControl.GreenLEDState = true;
      
      }
