#ifndef BOARD_h
#define BOARD_h

#include "Arduino.h"
#include "Wire.h"
#include "ZSC31050.h"
#include "ZSC31050Serial.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

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

		Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  private:

    HardwareSerial & serialHandler;

};
#endif