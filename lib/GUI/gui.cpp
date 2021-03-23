#include <gui.h>

void GUI::boot(void)
{
  board.begin();
  screenheader.show();
  currentScreen = 0; // MainMenu
  mainScreen.show();
}

void GUI::update(void)
{
  board.update();
  screenheader.update();
  switch (currentScreen) {
    case 0: //MainMenu
      mainScreen.update();
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
  }
}

void GUI::fastUpdate(void)
{
}

void GUI::updateTouch()
{
  TS_Point p = board.touchScreen.getPoint();
  TouchY = board.TFT.height() - p.x;
  TouchX = p.y;
  if (currentScreen == 0) {
    if (mainScreen.presSetPointButton.touched(TouchX, TouchY)) {
      mainScreen.presSetPointButton.touchHandle(mainScreen.presSetPointButton.touched(TouchX, TouchY));
      board.dac.setVoltage((int)(mainScreen.presSetPointButton.setPoint), false);
      return;
    }
  }
}