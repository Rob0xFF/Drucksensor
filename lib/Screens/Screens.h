#ifndef SCREENS_h
#define SCREENS_h

#include <new.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"
#include <board.h>
#include <Elements.h>

#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define TFT_GRAY 0x630C
#define TFT_BROWN 0x1924
#define TFT_OLIVE 0x234D
#define TFT_GREEN 0x9DAA
#define TFT_RED 0xD9E2

#define TOP_MARGIN 10
#define GRIDX 44
#define GRIDX_INTERSPACE 8
#define GRIDY 38
#define GRIDY_INTERSPACE 5

#define HOR 1
#define VERT 2

static uint16_t xCoord(uint8_t x){
	return x * GRIDX_INTERSPACE + (x - 1) * GRIDX;
}

static uint16_t xWidth(uint8_t w){
	return (w - 1) * GRIDX_INTERSPACE + w * GRIDX;
}

static uint16_t yCoord(uint8_t y){
	return TOP_MARGIN + y * GRIDY_INTERSPACE + (y - 1) * GRIDY;
}

static uint16_t yHeight(uint8_t h){
	return (h - 1) * GRIDY_INTERSPACE + h * GRIDY;
}

class ScreenHeader
{
  public:

    ScreenHeader(Board & myBoard): board(myBoard) {};

    void show(void);

    void update(void);

  private:

    Board & board;

    char tempStr[5] = "10.0";
    char humStr[5] = "10.0";

    float temperature = 10.0;
    float humidity = 10.0;

};

class MainScreen
{
  public:

    MainScreen(Board & myBoard): board(myBoard) {};

    void show(void);

    void update(void);

		Bridge bridge = Bridge(board, xCoord(3), yCoord(2));

  private:

    Board & board;

    char rawPressureStr[5] = "10.0";

    char pressureSIStr[5] = "10.0";

		uint16_t rawPressure = 0;

		float pressureSI = 0.0;

};

#endif