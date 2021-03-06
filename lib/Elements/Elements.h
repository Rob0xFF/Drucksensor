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

    char bridgeVoltageStr[10] = "00.00";

    char voltageStr[10] = "0.00";

    uint8_t bridgeVoltageTextWidth = 0;

    uint8_t voltageTextWidth = 0;

    float bridgeVoltage = 0.0;

    float voltage = 0.0;
};

template <class valType> class OutputBox
{
  public:

    OutputBox(Board & myBoard, int16_t x, int16_t y, const char * caption, const char * format, valType & val, uint16_t color, uint8_t halt): board(myBoard), _myX(x), _myY(y), _myCaption(caption), _myFormat(format), myVal(val), _myColor(color), _haltOnUSB(halt) {};

    void show(void);

    void update(void);

    void setColor(uint16_t color);

    Board & board;

  private:

    int16_t currentVal;

    char valueStr[7] = " ";

    uint8_t textWidth = 0;

    int16_t _myX;

    int16_t _myY;

    const char * _myCaption;

    const char * _myFormat;

    valType & myVal;

    uint16_t _myColor;

    uint8_t _haltOnUSB;

};

class RoundOutputBox
{
  public:

    RoundOutputBox(Board & myBoard, int16_t x, int16_t y, const char * caption, const char * format, float & val, const char * unit): board(myBoard), _myX(x), _myY(y), _myCaption(caption), _myFormat(format), myVal(val), _myUnit(unit) {};

    void show(void);

    void update(void);

    Board & board;

  private:

    int16_t currentVal;

    char valueStr[7] = " ";

    uint8_t textWidth = 0;

    int16_t _myX;

    int16_t _myY;

    const char * _myCaption;

    const char * _myFormat;

    float & myVal;

    const char * _myUnit;

};

class IDOutputBox
{
  public:

    IDOutputBox(Board & myBoard, int16_t x, int16_t y, const char * caption, const char * format, uint16_t & val, const char * unit): board(myBoard), _myX(x), _myY(y), _myCaption(caption), _myFormat(format), myVal(val), _myUnit(unit) {};

    void show(void);

    void update(void);

    Board & board;

  private:

    int16_t currentVal;

    char valueStr[7] = " ";

    uint8_t textWidth = 0;

    int16_t _myX;

    int16_t _myY;

    const char * _myCaption;

    const char * _myFormat;

    uint16_t & myVal;

    const char * _myUnit;

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

    pButton(Board & myboard, const char * caption, const int16_t x, const int16_t y, const int16_t width, const int16_t height, uint16_t color) : board(myboard), _caption(caption), _myX(x), _myY(y), _myWidth(width), _myHeight(height), _myColor(color) {};

    void show(void);

    void hide(void);

    uint8_t touched(int16_t x, int16_t y);

    void setColor(uint16_t color);

    Board & board;

  private:

    const char * _caption;
    const int16_t _myX;
    const int16_t _myY;
    const int16_t _myWidth;
    const int16_t _myHeight;
    uint16_t _myColor;

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