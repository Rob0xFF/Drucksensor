#ifndef BOARD_h
#define BOARD_h

#include "Arduino.h"
#include "Wire.h"
#include "ZSC31050.h"
#include "ZSC31050Serial.h"

class Board
{
  public:

    Board()
    {
    };

		void begin(void);

    void update(void);

		ZSC31050Serial extSerial = ZSC31050Serial();

		ZSC31050 pressureSensor = ZSC31050(0x78);

  private:

    HardwareSerial & serialHandler;

};
#endif