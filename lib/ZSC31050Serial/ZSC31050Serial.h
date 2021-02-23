#ifndef ZSC31050Serial_h
#define ZSC31050Serial_h

#include "Arduino.h"
#include "Wire.h"
#include "new.h"

#define ACK 0x06
#define CR 0x0D
#define LF 0x0A
#define COLON 0x3B
#define AT 0xA9

class ZSC31050Serial
{
  public:

    ZSC31050Serial()
    {
    };

    uint8_t parseSerialCommand(void);

    void handleSerialCommand(void);

    uint8_t isBusy(void);

  private:

    uint8_t hexchar2int(uint8_t start, uint8_t length);

    uint16_t decchar2int(uint8_t start, uint8_t length);

    char serialCommand[128];

    char firstValidChar = 'V';

    uint8_t serialCommandIndex = 0;

    uint16_t triggerDelay = 0;

    uint8_t busy = 0;

};
#endif