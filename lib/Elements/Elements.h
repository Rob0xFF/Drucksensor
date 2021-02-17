#ifndef ELEMENTS_h
#define ELEMENTS_h

#include <new.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"
#include <INA226.h>
#include <HIH61XX.h>
#include <display.h>
#include "glcdfont.c"
#include <Adafruit_FT6206.h>

#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define TFT_GRAY 0x630C
#define TFT_BROWN 0x1924
#define TFT_OLIVE 0x234D
#define TFT_GREEN 0x9DAA
#define TFT_RED 0xD9E2
#define TFT_ORANGE 0xFC60

#include <board.h>

class Bridge
{
	public:

    Bridge(Board & myBoard, int16_t x, int16_t y): board(myBoard), _myX(x), _myY(y) {};

    void show(void);

    void update(void);

    Board & board;

  private:

    int16_t _myX;

    int16_t _myY;

    char bridgeVoltageStr[6] = "00.00";

    char voltageStr[5] = "0.00";

		float bridgeVoltage = 0.0;

		float voltage = 0.0;
};

class rButton
{
  public:

    rButton(Board & myBoard, const float setPointMin, const float setPointMax, const float increment, const char * unit, const char * format, const int16_t x, const int16_t y, const int16_t width, const int16_t height, const uint8_t dir) : board(myBoard), setPointMin(setPointMin), setPointMax(setPointMax), _increment(increment), _unit(unit), _format(format), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myDir(dir)
    {
    };

    void show(void);

    void update(void);

    uint8_t touched(int16_t x, int16_t y);

    void touchHandle(uint8_t dir);

    Board & board;

    float setPoint = 0;

  private:

    const float setPointMin;
    const float setPointMax;
    const float _increment;
    const char * _unit;
    const char * _format;
    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;
    const uint8_t _myDir;

    char _caption[10];
    uint8_t _textWidth;

};

class pButton
{
  public:

    pButton(Board & myboard, const char * caption, const int16_t x, const int16_t y, const int16_t width, const int16_t height, const uint16_t color) : board(myboard), _caption(caption), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myColor(color) {};

    void show(void);

    void hide(void);

    uint8_t touched(int16_t x, int16_t y);

    Board & board;

  private:

    const char * _caption;
    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;
    const uint16_t _myColor;

};

class TextBox
{
  public:

    TextBox(Board & myboard, const char * caption, const int16_t x, const int16_t y, const int16_t width, const int16_t height) : board(myboard), _caption(caption), _myX(x), _myY(y), _myWidth(width), _myHeight(height) {};

    void show(void);

    Board & board;

  private:

    const char * _caption;
    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;

};

class sButton
{
  public:

    sButton(Board & myboard, const char * caption, const int16_t x, const int16_t y, const int16_t width, const int16_t height, const uint16_t color) : board(myboard), _caption(caption), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myColor(color) {};

    void show(void);

    void update(void);

    void hide(void);

    uint8_t touched(int16_t x, int16_t y);

    void touchHandle(void);

    Board & board;

    uint8_t selected = 0;

  private:

    const char * _caption;
    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;
    const uint16_t _myColor;

};

class WHZLogo
{
  public:

    WHZLogo(Board & myBoard, int16_t x, int16_t y): board(myBoard), _myX(x), _myY(y) {};

    void show(void);

    Board & board;

  private:

    int16_t _myX;
    int16_t _myY;
};

#endif