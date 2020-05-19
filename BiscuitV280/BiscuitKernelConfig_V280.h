/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 21.01.2018 15:19:48
 Libraries   :
 Author      :
 Description :
******************************************************************/

//  Define Watch Dog Timer Period.  
const unsigned int HeartBeatPerioduS = 200;     // HeartBeatPeriod in uS 
const unsigned int WatchDogCount = 25000;       // = Number milliseconds before WDT triggers*1000/HeartBeatPerioduS.  Must be less than 50000
// Define Length of loop for 100% utilisation in ms
const int MaxLoopLength = 100;
// MaxPriorityTested is the highest priority a task can be given - anything greater is the same
// So if MaxPriorityTested is 3, then a priority of 4,5,6 ... is the same as 3, but a priority of 2 is lower.
const int MaxPriorityTested = 3;
// Define the times of the sign on flash interval in mS
const int FlashTimemS = 500;
const int LongFlashTimemS = 750;

