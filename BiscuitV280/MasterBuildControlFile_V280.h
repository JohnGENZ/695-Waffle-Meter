/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 20.01.2018 16:35:47
 Libraries   :
 Author      :
 Description :
******************************************************************/

// Hardware Configuration Files for this build
#include "BuildConfig_V280.h"         // Comms Config for this build
#include "HardwareConfig_V280.h"      // Hardware Config for this build
#include "DebugUtils.h"               // Utils to support debug - see https://github.com/SensorsIot/Pre-Compiler-Directives
#include "ArduinoTrace.h"             // Trace Library - see https://github.com/bblanchon/ArduinoTrace  https://techtutorialsx.com/2018/10/11/esp32-esp8266-arduino-debugging-with-the-arduinotrace-library/#more-26363

// System Libraries
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/atomic.h>              // https://www.nongnu.org/avr-libc/user-manual/group__util__atomic.html
#include <EEPROM.h>
#include <TimerOne.h>                 // Support for Heartbeat timer https://www.pjrc.com/teensy/td_libs_TimerOne.html, https://github.com/PaulStoffregen/TimerOne

// Core Support Libraries
#include "EEPROMUtils_V280.h"                    // Utils to make the EEPROM a little bit more like the ESP32 NVS

// Biscuit Task Config Files
#include "RedFlashConfig_V280.h"                 // Red Flash Config
#include "BiscuitEnvironmentConfig_V280.h"       // Config constants for the Environment Build
#include "BiscuitKernelConfig_V280.h"            // Kernel Config
#include "ButtonsConfig_V280.h"                  // Respond to button state Config 
#include "LightsConfig_V280.h"                   // Update lights Config     
#include "GSICalcConfig_V280.h"                  // Process ADC readings and update GSI value Config 
#include "InsideOutConfig_V280.h"                // Diagnostic Task to output data to the LED pins Config

// Biscuit Task Data Files
#include "RedFlashData_V280.h"                   // Red Flash Data
#include "BiscuitEnvironmentData_V280.h"         // Data constants for the Environment Build
#include "BiscuitKernelData_V280.h"              // Kernel Level Data
#include "ButtonsData_V280.h"                    // Respond to button state Data 
#include "LightsData_V280.h"                     // Update lights Data     
#include "GSICalcData_V280.h"                    // Process ADC readings and update GSI value Data 
#include "InsideOutData_V280.h"                  // Diagnostic Task to output data to the LED pins Data

// Biscuit Task Utilities
#include "BiscuitKernelUtils_V280.h"            // Kernel Support Utilities 
#include "RedFlashUtils_V280.h"                 // Red Flash Utilities
#include "ButtonsUtils_V280.h"                  // Respond to button state Utils 
#include "LightsUtils_V280.h"                   // Update lights Utils     
#include "GSICalcUtils_V280.h"                  // Process ADC readings and update GSI value Utils 
#include "InsideOutUtils_V280.h"                // Diagnostic Task to output data to the LED pins Utils
#include "BiscuitEnvironmentUtils_V280.h"       // Utilities for the Environment Build

// Task State Saver Routines can point to Utils
#include "TaskStateSaver_V280.h"                // The calls that save task state

// Interrupt Routines
#include "InterruptProcess_V280.h"              // Interrupt Processing Routines

// Hardware Configuration Utilities
#include "BiscuitKernelHWUtils_V280.h"          // Core HW Config 

// Biscuit Task Code 
#include "BiscuitEnvironmentCode_V280.h"        // Code to build Environment environment
#include "RedFlashCode_V280.h"                  // Red Flash
#include "ButtonsCode_V280.h"                   // Respond to button state Code 
#include "LightsCode_V280.h"                    // Update lights Code     
#include "GSICalcCode_V280.h"                   // Process ADC readings and update GSI value Code 
#include "InsideOutCode_V280.h"                 // Diagnostic Task to output data to the LED pins Code

// Biscuit Kernel Code
#include "BiscuitKernelCode_V280.h"             // Kernel Code


/*
String TestText = String("It was a beautiful day on the Island of Sodor. Thomas was high in the hills, bringing some") += \
                  String(" freight cars to the wharf. At an unfamiliar junction, he saw an old, overgrown track that") += \
                  String(" looked like a shortcut.  Soon he was rattling down the steep track. ""No one has been down") += \
                  String(" here for a very long time!"" he huffed. Then Thomas gasped. ""Fizzling fireboxes!"" ");
                  
*/