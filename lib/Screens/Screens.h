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
#define TFT_GREEN2 0x9DAA
#define TFT_RED 0xF920
#define TFT_RED2 0xD9E2
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

    ~MainScreen()
    {
      board.TFT.fillRect(xCoord(1), yCoord(1), xWidth(6), yHeight(5), TFT_BLACK);
    };

    void show(void);

    void update(void);

    Board & board;

    Bridge bridge = Bridge(board, xCoord(3), yCoord(2));

    OutputBox <float> senOutSIBox = OutputBox<float>(board, xCoord(1), yCoord(1), " P (hPa) ", "%1.1f", board.P_SI, TFT_WHITE, 1);

    OutputBox <int16_t> senOutBox = OutputBox<int16_t>(board, xCoord(1), yCoord(2), " P ", "%1d", board.P, TFT_WHITE, 1);

    OutputBox <int16_t> senT1Box = OutputBox<int16_t>(board, xCoord(1), yCoord(3), " T1 ", "%1d", board.T1, TFT_WHITE, 1);

    OutputBox <int16_t> senT2Box = OutputBox<int16_t>(board, xCoord(1), yCoord(4), " T2 ", "%1d", board.T2, TFT_WHITE, 1);

    IDOutputBox idBox = IDOutputBox(board, xCoord(3), yCoord(1), "ZSC", "%03d", board.senChipID, "ID");

    RoundOutputBox tempBox = RoundOutputBox(board, xCoord(4), yCoord(1), "T", "%1.1f", board.senTemperature, "\247C");

    RoundOutputBox humBox = RoundOutputBox(board, xCoord(5), yCoord(1), "HUM", "%1.1f", board.senHumidity, "%");

    RoundOutputBox presBox = RoundOutputBox(board, xCoord(6), yCoord(1), "P", "%1.1f", board.mprPres, "hPa");

    rButton presSetPointButton = rButton(board, 0.0, 100.0, 5, "%", "%1.0f%s", xCoord(1), yCoord(5), xWidth(2), yHeight(1), HOR);

    pButton calButton = pButton(board, "Calibration", xCoord(3), yCoord(5), xWidth(2), yHeight(1), TFT_GREEN2);

    pButton infoButton = pButton(board, "Info", xCoord(5), yCoord(5), xWidth(2), yHeight(1), TFT_OLIVE);

  private:

};

class CalScreen
{
  public:

    CalScreen(Board & myBoard): board(myBoard) {};

    ~CalScreen()
    {
      board.TFT.fillRect(xCoord(1), yCoord(1), xWidth(6), yHeight(5), TFT_BLACK);
    }

    void show(void);

    void update(void);

    Board & board;

    TextBox setMaxText = TextBox(board, "Cal. Pres. Max.", xCoord(1), yCoord(1), xWidth(2), yHeight(1));

    TextBox setPercentText = TextBox(board, "Cal. Pres. %", xCoord(1), yCoord(2), xWidth(2), yHeight(1));

    TextBox setMinText = TextBox(board, "Cal. Pres. Min.", xCoord(1), yCoord(3), xWidth(2), yHeight(1));

    rButton setMaxButton = rButton(board, 5.0, 480.0, 10, "hPa", "%1.0f%s", xCoord(3), yCoord(1), xWidth(2), yHeight(1), HOR);

    rButton setMinButton = rButton(board, 0.0, 470.0, 10, "hPa", "%1.0f%s", xCoord(3), yCoord(3), xWidth(2), yHeight(1), HOR);

    rButton setPercentButton = rButton(board, 0.0, 100.0, 5, "%", "%1.0f%s", xCoord(3), yCoord(2), xWidth(2), yHeight(1), HOR);

    OutputBox <float> presBox = OutputBox<float>(board, xCoord(5), yCoord(2), " dP (hPa) ", "%1.1f", board.mprPresRelative, TFT_RED, 0);

    pButton zeroButton = pButton(board, "AUTOZERO", xCoord(5), yCoord(3), xWidth(2), yHeight(1), TFT_RED2);

    TextBox setTempText = TextBox(board, "Temp.", xCoord(1), yCoord(4), xWidth(2), yHeight(1));

    rButton setTempButton = rButton(board, 0.0, 40, 1.0, "C", "%1.0f%s", xCoord(3), yCoord(4), xWidth(2), yHeight(1), HOR);

    OutputBox <float> tempBox = OutputBox<float>(board, xCoord(5), yCoord(4), " T (C) ", "%1.1f", board.senTemperature, TFT_RED, 0);

    pButton exitButton = pButton(board, "EXIT", xCoord(1), yCoord(5), xWidth(4), yHeight(1), TFT_RED2);

    pButton envButton = pButton(board, "ENV. CHAMBER", xCoord(5), yCoord(5), xWidth(2), yHeight(1), TFT_OLIVE);

    uint8_t zeroing = 3;

    uint8_t adjusting = 5;

    float goal = 0.0;

    int dacGoal = 0;

    float corr = 0.0;

    uint8_t newTemp = 1;

  private:

};

class EnvScreen
{
  public:

    EnvScreen(Board & myBoard): board(myBoard) {};

    ~EnvScreen()
    {
      board.TFT.fillRect(xCoord(1), yCoord(1), xWidth(6), yHeight(5), TFT_BLACK);
    }

    void show(void);

    void update(void);

    Board & board;

    OutputBox <float> TempSetPointBox = OutputBox<float>(board, xCoord(3), yCoord(2), " T SP (C) ", "%1.1f", board.envChamber.TS, TFT_WHITE, 0);

    OutputBox <float> HumSetPointBox = OutputBox<float>(board, xCoord(3), yCoord(3), " Hum SP (%) ", "%1.0f", board.envChamber.HS, TFT_WHITE, 0);

    OutputBox <float> TBox = OutputBox<float>(board, xCoord(5), yCoord(2), " T (C) ", "%1.1f", board.envChamber.T, TFT_WHITE, 0);

    OutputBox <float> HumBox = OutputBox<float>(board, xCoord(5), yCoord(3), " Hum (%) ", "%1.0f", board.envChamber.H, TFT_WHITE, 0);

    pButton exitButton = pButton(board, "EXIT", xCoord(5), yCoord(5), xWidth(2), yHeight(1), TFT_RED2);

  private:

};

class InfoScreen
{
  public:

    InfoScreen(Board & myBoard): board(myBoard) {};

    ~InfoScreen()
    {
      board.TFT.fillRect(xCoord(1), yCoord(1), xWidth(6), yHeight(5), TFT_BLACK);
    }

    void show(void);

    void update(void);

    Board & board;

    pButton exitButton = pButton(board, "EXIT", xCoord(5), yCoord(5), xWidth(2), yHeight(1), TFT_RED2);

  private:

};

#endif