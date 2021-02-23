#ifndef BOARD_h
#define BOARD_h

#include "Arduino.h"
#include "Wire.h"
#include "ZSC31050.h"
#include "ZSC31050Serial.h"

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <display.h>
#include <new.h>
#include <Adafruit_FT6206.h>
#include <HIH61XX.h>
#include <INA226.h>
#include <EEPROM.h>


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

     Adafruit_FT6206 touchScreen = Adafruit_FT6206();
 
		Display TFT = Display();

  	INA226 voltageSensor = INA226();

    HIH61XX HIH = HIH61XX(0x27, 255);

		float temperature = 0.0;

		float humidity = 0.0;

		float bridgeVoltage = 0.0;

		float voltage = 0.0;

		int16_t rawP;

		int16_t correctedP;

		float correctedP_SI;

		int16_t rawT1;

  private:


};
#endif