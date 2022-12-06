#ifndef ZSC31050Serial_h
#define ZSC31050Serial_h

#include "Arduino.h"
#include "Wire.h"
#include "new.h"

#include <EEPROM.h>

class ZSC31050Serial
{
  public:

    ZSC31050Serial(HardwareSerial & s): serialHandler(s) {};

    uint8_t parseSerialCommand(void);

    void handleSerialCommand(void);

    uint8_t isBusy(void);
    
    uint8_t isNewCalibration = 0;

    uint8_t isConnected(void);

    void disConnect(void);

    uint16_t senChipID = 0;

    HardwareSerial & serialHandler;

  private:

    uint8_t hexchar2int(uint8_t start);

    uint16_t decchar2int(uint8_t start);

    char serialCommand[128];

    char firstValidChar = 'V';

    uint8_t serialCommandIndex = 0;

    uint16_t triggerDelay = 0;

    uint8_t connected = 0;

    uint8_t busy = 0;

    const char CR = 0x0D;
    const char LF = 0x0A;
    const char COLON = 0x3B;
    const char AT = 0xA9;
    const char ACK = 0x06;

};
#endif