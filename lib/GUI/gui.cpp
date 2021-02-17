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
}

void GUI::fastUpdate(void)
{
}

void GUI::updateTouch()
{
  TS_Point p = board.touchScreen.getPoint();
  TouchY = board.TFT.height() - p.x;
  TouchX = p.y;
}