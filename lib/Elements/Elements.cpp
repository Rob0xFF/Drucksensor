#include <Elements.h>

void Bridge::show(void)
{
	board.TFT.drawLine(_myX + 74, _myY + 9, _myX + 56, _myY + 27, TFT_WHITE);
	board.TFT.drawLine(_myX + 74, _myY + 9, _myX + 92, _myY + 27, TFT_WHITE);
	board.TFT.drawLine(_myX + 39, _myY + 44, _myX + 21, _myY + 62, TFT_WHITE);
	board.TFT.drawLine(_myX + 109, _myY + 44, _myX + 127, _myY + 62, TFT_WHITE);

	board.TFT.drawLine(_myX + 21, _myY + 62, _myX + 39, _myY + 80, TFT_WHITE);
	board.TFT.drawLine(_myX + 127, _myY + 62, _myX + 109, _myY + 80, TFT_WHITE);
	board.TFT.drawLine(_myX + 56, _myY + 97, _myX + 74, _myY + 115, TFT_WHITE);
	board.TFT.drawLine(_myX + 92, _myY + 97, _myX + 74, _myY + 115, TFT_WHITE);

	board.TFT.drawLine(_myX + 53, _myY + 24, _myX + 59, _myY + 30, TFT_WHITE);
	board.TFT.drawLine(_myX + 53, _myY + 24, _myX + 36, _myY + 41, TFT_WHITE);
	board.TFT.drawLine(_myX + 36, _myY + 41, _myX + 42, _myY + 47, TFT_WHITE);
	board.TFT.drawLine(_myX + 42, _myY + 47, _myX + 59, _myY + 30, TFT_WHITE);

	board.TFT.drawLine(_myX + 95, _myY + 24, _myX + 112, _myY + 41, TFT_WHITE);
	board.TFT.drawLine(_myX + 112, _myY + 41, _myX + 106, _myY + 47, TFT_WHITE);
	board.TFT.drawLine(_myX + 106, _myY + 47, _myX + 89, _myY + 30, TFT_WHITE);
	board.TFT.drawLine(_myX + 89, _myY + 30, _myX + 95, _myY + 24, TFT_WHITE);

	board.TFT.drawLine(_myX + 42, _myY + 77, _myX + 59, _myY + 94, TFT_WHITE);
	board.TFT.drawLine(_myX + 59, _myY + 94, _myX + 53, _myY + 100, TFT_WHITE);
	board.TFT.drawLine(_myX + 53, _myY + 100, _myX + 36, _myY + 83, TFT_WHITE);
	board.TFT.drawLine(_myX + 36, _myY + 83, _myX + 42, _myY + 77, TFT_WHITE);

	board.TFT.drawLine(_myX + 106, _myY + 77, _myX + 112, _myY + 83, TFT_WHITE);
	board.TFT.drawLine(_myX + 112, _myY + 83, _myX + 95, _myY + 100, TFT_WHITE);
	board.TFT.drawLine(_myX + 95, _myY + 100, _myX + 89, _myY + 94, TFT_WHITE);
	board.TFT.drawLine(_myX + 89, _myY + 94, _myX + 106, _myY + 77, TFT_WHITE);

	board.TFT.drawLine(_myX + 74, _myY + 9, _myX + 178, _myY + 9, TFT_WHITE);
	board.TFT.drawLine(_myX + 178, _myY + 9, _myX +178, _myY + 43, TFT_WHITE);
	board.TFT.drawLine(_myX + 177, _myY + 81, _myX + 177, _myY + 115, TFT_WHITE);
	board.TFT.drawLine(_myX + 177, _myY + 115, _myX + 74, _myY + 115, TFT_WHITE);

	board.TFT.drawLine(_myX + 21, _myY + 62, _myX + 44, _myY + 62, TFT_WHITE);
	board.TFT.drawLine(_myX + 104, _myY + 62, _myX + 127, _myY + 62, TFT_WHITE);

	board.TFT.fillCircle(_myX + 74, _myY + 9, 2, TFT_WHITE);
	board.TFT.fillCircle(_myX + 21, _myY + 62, 2, TFT_WHITE);
	board.TFT.fillCircle(_myX + 74, _myY + 115, 2, TFT_WHITE);
	board.TFT.fillCircle(_myX + 127, _myY + 62, 2, TFT_WHITE);
}

void Bridge::update(void)
{
	if(voltage != board.voltage) {
		voltage = board.voltage;
  	board.TFT.setTextSize(1);
  	board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
		uint8_t newWidth = snprintf(voltageStr, 10, "%2.1f%s", voltage, "mV");
		if(voltageTextWidth != newWidth) {
			board.TFT.fillRect(_myX + 53, _myY + 58, 56, 8, TFT_BLACK);
			voltageTextWidth = newWidth;
		}
  	board.TFT.setCursor(_myX + 74 - 6 * voltageTextWidth / 2, _myY + 58);
  	board.TFT.print(voltageStr);
	}
	if(bridgeVoltage != board.bridgeVoltage) {
		bridgeVoltage = board.bridgeVoltage;
  	board.TFT.setTextSize(1);
  	board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
		uint8_t newWidth = snprintf(bridgeVoltageStr, 10, "%1.2f%s", bridgeVoltage, "V");
		if(bridgeVoltageTextWidth != newWidth) {
			board.TFT.fillRect(_myX + 160, _myY + 58, 36, 8, TFT_BLACK);
			bridgeVoltageTextWidth = newWidth;
		}
  	board.TFT.setCursor(_myX + 178 - 6 * bridgeVoltageTextWidth / 2, _myY + 58);
  	board.TFT.print(bridgeVoltageStr);
	}
}

void OutputBox::show(void) 
{
	board.TFT.drawRect(_myX, _myY, 96, 38, TFT_WHITE);
	board.TFT.setCursor(_myX + 2, _myY + 2);
	board.TFT.print(_myCaption);
}

void OutputBox::update(void) 
{
	board.TFT.setTextSize(2);
  board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
	uint8_t newWidth = snprintf(valueStr, 7, "%d", myVal);
	if(textWidth != newWidth) {
		board.TFT.fillRect(_myX + 12, _myY + 17, 72, 16, TFT_BLACK);
		textWidth = newWidth;
	}
  board.TFT.setCursor(_myX + 48 - 12 * textWidth / 2, _myY + 17);
	board.TFT.print(myVal);
	board.TFT.setTextSize(1);
}

void rButton::show(void)
{
  board.TFT.drawRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_WHITE);
  board.TFT.fillRoundRect(_myX + 1, _myY + 1, _myWidth - 2, _myHeight - 2, 3, TFT_OLIVE);
  board.TFT.setTextColor(TFT_WHITE, TFT_OLIVE);
  board.TFT.setTextSize(2);
  if (_myDir == 1) { //horizontal
    board.TFT.setCursor(_myX + _myWidth / 6 - 6, _myY + _myHeight / 2 - 7);
    board.TFT.print("-");
    board.TFT.setCursor(_myX + _myWidth * 5 / 6 - 6, _myY + _myHeight / 2 - 7);
    board.TFT.print("+");
  }
  if (_myDir == 2) { //vertical
    board.TFT.setCursor(_myX + _myWidth / 2 - 6, _myY + _myHeight / 6 - 7);
    board.TFT.print("+");
    board.TFT.setCursor(_myX + _myWidth / 2 - 6, _myY + _myHeight * 5 / 6 - 7);
    board.TFT.print("-");
  }
  board.TFT.setTextSize(1);
  _textWidth = snprintf(_caption, 10, _format, setPoint, _unit);
  board.TFT.setCursor(_myX + _myWidth / 2 - 6 * _textWidth / 2, _myY + _myHeight / 2 - 4);
  board.TFT.print(_caption);
}

void rButton::update(void)
{
  board.TFT.setTextSize(1);
  board.TFT.setTextColor(TFT_WHITE, TFT_OLIVE);
  board.TFT.fillRect(_myX + _myWidth / 2 - 6 * _textWidth / 2, _myY + _myHeight / 2 - 4, 6 * _textWidth, 8, TFT_OLIVE);
  board.TFT.setTextSize(1);
  _textWidth = snprintf(_caption, 10, _format, setPoint, _unit);
  board.TFT.setCursor(_myX + _myWidth / 2 - 6 * _textWidth / 2, _myY + _myHeight / 2 - 4);
  board.TFT.print(_caption);
}

uint8_t rButton::touched(int16_t x, int16_t y)
{
  if (_myDir == 2) {
    if ((x > _myX) && (x < _myX + _myWidth)) {
      if ((y > _myY) && (y < _myY + _myHeight / 3)) {
        return 1; // +
      }
      if ((y > _myY + _myHeight * 2 / 3) && (y < _myY + _myHeight)) {
        return 2; // -
      }
    }
  }
  if (_myDir == 1) {
    if ((y > _myY) && (y < _myY + _myHeight)) {
      if ((x > _myX) && (x < _myX + _myWidth / 3)) {
        return 2; // -
      }
      if ((x > _myX + _myWidth * 2 / 3) && (x < _myX + _myWidth)) {
        return 1; // +
      }
    }
  }
  return 0;
}

void rButton::touchHandle(uint8_t dir)
{
  if (dir == 1 && setPoint < setPointMax) {
    setPoint += _increment;
  }
  if (dir == 2 && setPoint > setPointMin) {
    setPoint -= _increment;
  }
  update();
}

void pButton::show(void)
{
  board.TFT.drawRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_WHITE);
  board.TFT.fillRoundRect(_myX + 1, _myY + 1, _myWidth - 2, _myHeight - 2, 3, _myColor);
  board.TFT.setTextColor(TFT_WHITE, _myColor);
  board.TFT.setCursor(_myX + _myWidth / 2 - (6 * strlen(_caption) / 2), _myY + _myHeight / 2 - 4);
  board.TFT.print(_caption);
}

void pButton::hide(void)
{
  board.TFT.fillRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_BLACK);
}

uint8_t pButton::touched(int16_t x, int16_t y)
{
  if ((x > _myX) && (x < _myX + _myWidth)) {
    if ((y > _myY) && (y < _myY + _myHeight)) {
      return true;
    }
  }
  return false;
}

void TextBox::show(void)
{
  board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
  board.TFT.setCursor(_myX + _myWidth / 2 - (6 * strlen(_caption) / 2), _myY + _myHeight / 2 - 4);
  board.TFT.print(_caption);
}

void sButton::show(void)
{
  board.TFT.drawRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_WHITE);
  board.TFT.fillRoundRect(_myX + 1, _myY + 1, _myWidth - 2, _myHeight - 2, 3, _myColor);
  board.TFT.drawCircle(_myX + _myWidth / 2, _myY + _myHeight / 3, 8, TFT_WHITE);
  board.TFT.setTextColor(TFT_WHITE, _myColor);
  board.TFT.setCursor(_myX + _myWidth / 2 - (6 * strlen(_caption) / 2), _myY + 2 * _myHeight / 3);
  board.TFT.print(_caption);
}

void sButton::update(void)
{
  board.TFT.fillCircle(_myX + _myWidth / 2, _myY + _myHeight / 3, 5, _myColor);
  if (selected) {
    board.TFT.fillCircle(_myX + _myWidth / 2, _myY + _myHeight / 3, 5, TFT_WHITE);
  }
}

void sButton::hide(void)
{
  board.TFT.fillRoundRect(_myX, _myY, _myWidth, _myHeight, 4, TFT_BLACK);
}

uint8_t sButton::touched(int16_t x, int16_t y)
{
  if ((x > _myX) && (x < _myX + _myWidth)) {
    if ((y > _myY) && (y < _myY + _myHeight)) {
      return true;
    }
  }
  return false;
}

void sButton::touchHandle(void)
{
  if (selected == 0) {
    selected = 1;
  } else if (selected == 1) {
    selected = 0;
  }
  update();
}

void WHZLogo::show()   // 108 x 108 px
{
  board.TFT.drawLine(_myX + 53, _myY + 0, _myX + 0, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 53, _myY + 1, _myX + 1, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 54, _myY + 0, _myX + 107, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 54, _myY + 1, _myX + 107, _myY + 54, TFT_WHITE);
  board.TFT.drawLine(_myX + 1, _myY + 54, _myX + 54, _myY + 107, TFT_WHITE);
  board.TFT.drawLine(_myX + 2, _myY + 54, _myX + 54, _myY + 106, TFT_WHITE);
  board.TFT.drawLine(_myX + 55, _myY + 106, _myX + 106, _myY + 55, TFT_WHITE);
  board.TFT.drawLine(_myX + 55, _myY + 105, _myX + 106, _myY + 54, TFT_WHITE);
  board.TFT.drawLine(_myX + 54, _myY + 105, _myX + 105, _myY + 54, TFT_WHITE);
  board.TFT.drawLine(_myX + 54, _myY + 104, _myX + 105, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 53, _myY + 104, _myX + 104, _myY + 53, TFT_WHITE);
  board.TFT.drawLine(_myX + 53, _myY + 103, _myX + 104, _myY + 52, TFT_WHITE);
  board.TFT.drawLine(_myX + 36, _myY + 19, _myX + 71, _myY + 19, TFT_WHITE);
  board.TFT.drawLine(_myX + 33, _myY + 84, _myX + 71, _myY + 84, TFT_WHITE);
  board.TFT.drawLine(_myX + 32, _myY + 83, _myX + 72, _myY + 83, TFT_WHITE);
  board.TFT.drawLine(_myX + 31, _myY + 82, _myX + 73, _myY + 82, TFT_WHITE);
  board.TFT.drawLine(_myX + 32, _myY + 81, _myX + 74, _myY + 81, TFT_WHITE);
  board.TFT.drawLine(_myX + 32, _myY + 80, _myX + 75, _myY + 80, TFT_WHITE);
  board.TFT.drawLine(_myX + 35, _myY + 79, _myX + 73, _myY + 21, TFT_WHITE);
  board.TFT.drawLine(_myX + 34, _myY + 79, _myX + 72, _myY + 21, TFT_WHITE);
  board.TFT.drawLine(_myX + 33, _myY + 79, _myX + 72, _myY + 20, TFT_WHITE);
}
