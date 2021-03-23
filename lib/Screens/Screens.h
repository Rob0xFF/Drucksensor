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
#define TFT_GREEN 0x07C0
#define TFT_RED 0xF920
#define TFT_ORANGE 0xFE47
#define TFT_BLUE 0x063F

#define TOP_MARGIN 10
#define GRIDX 44
#define GRIDX_INTERSPACE 8
#define GRIDY 38
#define GRIDY_INTERSPACE 5

#define HOR 1
#define VERT 2

static uint16_t xCoord(uint8_t x)
{
  return x * GRIDX_INTERSPACE + (x - 1) * GRIDX;
}

static uint16_t xWidth(uint8_t w)
{
  return (w - 1) * GRIDX_INTERSPACE + w * GRIDX;
}

static uint16_t yCoord(uint8_t y)
{
  return TOP_MARGIN + y * GRIDY_INTERSPACE + (y - 1) * GRIDY;
}

static uint16_t yHeight(uint8_t h)
{
  return (h - 1) * GRIDY_INTERSPACE + h * GRIDY;
}

class ScreenHeader
{
  public:

    ScreenHeader(Board & myBoard): board(myBoard) {};

    void show(void);

    void update(void);

    Board & board;

  private:

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

    Board & board;

    Bridge bridge = Bridge(board, xCoord(3), yCoord(2));

    OutputBox <float> senOutSIBox = OutputBox<float>(board, xCoord(1), yCoord(1), " P (hPa) ", "%1.1f", board.P_SI);

    OutputBox <int16_t> senOutBox = OutputBox<int16_t>(board, xCoord(1), yCoord(2), " P ", "%1d", board.P);

    OutputBox <int16_t> senT1Box = OutputBox<int16_t>(board, xCoord(1), yCoord(3), " T1 ", "%1d", board.T1);

    OutputBox <int16_t> senT2Box = OutputBox<int16_t>(board, xCoord(1), yCoord(4), " T2 ", "%1d", board.T2);

    IDOutputBox idBox = IDOutputBox(board, xCoord(3), yCoord(1), "ZSC", "%03d", board.senChipID, "ID");

    RoundOutputBox tempBox = RoundOutputBox(board, xCoord(4), yCoord(1), "T", "%1.1f", board.senTemperature, "\247C");

    RoundOutputBox humBox = RoundOutputBox(board, xCoord(5), yCoord(1), "HUM", "%1.1f", board.senHumidity, "\%");

    RoundOutputBox presBox = RoundOutputBox(board, xCoord(6), yCoord(1), "P", "%1.1f", board.mprPres, "hPa");

    rButton presSetPointButton = rButton(board, 0.0, 4095.0, 50, "", "%1.0f%s", xCoord(1), yCoord(5), xWidth(2), yHeight(1), HOR);

    pButton correctionButton = pButton(board, "ZSC Raw", xCoord(3), yCoord(5), xWidth(2), yHeight(1), TFT_OLIVE);

    pButton outputButton = pButton(board, "Info", xCoord(5), yCoord(5), xWidth(2), yHeight(1), TFT_OLIVE);

  private:

    char rawPressureStr[5] = "10.0";

    char pressureSIStr[5] = "10.0";

    uint16_t rawPressure = 0;

    float pressureSI = 0.0;

};

#endif