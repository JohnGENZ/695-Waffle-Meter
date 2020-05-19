/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 09.08.2019 16:49:17
 Libraries   :
 Author      :
 Description :
******************************************************************/

// http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/reference.html
// http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/libraries.html
// https://github.com/esp8266/Arduino/tree/master/libraries/EEPROM
// https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences  


int32_t EEProm_get_int32_t (uint8_t ByteAddress) {

          int32_t localData;

          EEPROM.get(int(ByteAddress), localData);
          return localData;
          
          }
          
void EEProm_put_int32_t(uint8_t ByteAddress, int32_t DataToSave) {

          EEPROM.put(int(ByteAddress), DataToSave);
      
          }

int16_t EEProm_get_int16_t (uint8_t ByteAddress) {

          int16_t localData;

          EEPROM.get(int(ByteAddress), localData);
          return localData;
          
          }
          
void EEProm_put_int16_t(uint8_t ByteAddress, int16_t DataToSave) {

          EEPROM.put(int(ByteAddress), DataToSave);
      
          }          
          
          
float EEProm_get_float (uint8_t ByteAddress) {

          union localRawData {float fVal; int32_t iVal; byte bVal[4];};

          byte localDatabyte;
          localRawData localData;
          
          localData.bVal[0]=localDatabyte=EEPROM.read(ByteAddress);
          localData.bVal[1]=localDatabyte=EEPROM.read(ByteAddress+1); 
          localData.bVal[2]=localDatabyte=EEPROM.read(ByteAddress+2); 
          localData.bVal[3]=localDatabyte=EEPROM.read(ByteAddress+3);           

          return localData.fVal;  
          }
          
void EEProm_put_float(uint8_t ByteAddress, float DataToSave) {
          union localRawData {float fVal; int32_t iVal; byte bVal[4];};

          byte localDatabyte;
          localRawData localData;
          
          localData.fVal = DataToSave;

          EEPROM.write(ByteAddress, localData.bVal[0]);
          EEPROM.write(ByteAddress+1, localData.bVal[1]);
          EEPROM.write(ByteAddress+2, localData.bVal[2]);           
          EEPROM.write(ByteAddress+3, localData.bVal[3]); 

          }


byte EEProm_get_UChar (uint8_t ByteAddress) {

          byte localDatabyte;
          
          localDatabyte=localDatabyte=EEPROM.read(ByteAddress);

          return localDatabyte;  
          }
          
void EEProm_put_UChar(uint8_t ByteAddress, byte DataToSave) {
          
          EEPROM.write(ByteAddress, DataToSave);

          }    
          
          
bool EEProm_get_Bool(uint8_t ByteAddress) {

    if (EEProm_get_UChar(ByteAddress) == 1) return true;
    return false;
    }  

void EEProm_put_Bool(uint8_t ByteAddress, bool DataToSave){

    byte localDatabyte;

    localDatabyte=0;
    if (DataToSave==true) localDatabyte=1;
    EEProm_put_UChar(ByteAddress, localDatabyte);
    } 
   
   
void EEProm_get_Bytes(uint8_t ByteAddress, char* ByteBuf, int32_t ByteCount) {

    for (int32_t i=0;i<ByteCount; i++) ByteBuf[i] = EEPROM.read(ByteAddress+i); 

    }  

void EEProm_put_Bytes(uint8_t ByteAddress, char* ByteBuf, int32_t ByteCount){

    for (int32_t i=0;i<ByteCount; i++) EEPROM.write((ByteAddress+i),ByteBuf[i]); 

    }      

