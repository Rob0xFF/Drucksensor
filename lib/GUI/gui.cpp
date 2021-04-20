#include <gui.h>

void GUI::boot(void)
{
  board.begin();
  screenheader.show();
  currentScreen = 0;
  mainScreen = new (memBufferMainScreen) MainScreen(board);
  mainScreen -> show();
}

void GUI::update(void)
{
  board.update();
  screenheader.update();
  switch (currentScreen) {
    case 0: //MainMenu
      mainScreen -> update();
      break;
    case 1:
      calScreen -> update();
      break;
    case 2:
      envScreen -> update();
      break;
    case 3:
      infoScreen -> update();
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
    if (mainScreen -> presSetPointButton.touched(TouchX, TouchY)) {
      mainScreen -> presSetPointButton.touchHandle(mainScreen -> presSetPointButton.touched(TouchX, TouchY));
      board.dac.setVoltage((int)(40.95 * mainScreen -> presSetPointButton.setPoint), false);
      return;
    }
    if (mainScreen -> calButton.touched(TouchX, TouchY)) {
      mainScreen -> ~MainScreen();
      currentScreen = 1;
      calScreen = new (memBufferCalScreen) CalScreen(board);
      calScreen -> setMaxButton.setPoint = 480.0;
      calScreen -> setMinButton.setPoint = 0.0;
      calScreen -> show();
      return;
    }
    if (mainScreen -> infoButton.touched(TouchX, TouchY)) {
      mainScreen -> ~MainScreen();
      currentScreen = 3;
      infoScreen = new (memBufferInfoScreen) InfoScreen(board);
      infoScreen -> show();
      return;
    }
  }
  if (currentScreen == 1) { // CalScreen
    if (calScreen -> setMaxButton.touched(TouchX, TouchY)) {
      calScreen -> setMaxButton.touchHandle(calScreen -> setMaxButton.touched(TouchX, TouchY));
      if (calScreen -> setMaxButton.setPoint <= calScreen -> setMinButton.setPoint) {
        calScreen -> setMinButton.setPoint -= 10;
        calScreen -> setMinButton.update();
      }
      calScreen -> corr = 0;
      calScreen -> adjusting = 3;
      calScreen -> update();
      return;
    }
    if (calScreen -> setPercentButton.touched(TouchX, TouchY)) {
      calScreen -> setPercentButton.touchHandle(calScreen -> setPercentButton.touched(TouchX, TouchY));
      calScreen -> corr = 0;
      calScreen -> adjusting = 3;
      calScreen -> update();
      return;
    }
    if (calScreen -> setMinButton.touched(TouchX, TouchY)) {
      calScreen -> setMinButton.touchHandle(calScreen -> setMinButton.touched(TouchX, TouchY));
      if (calScreen -> setMinButton.setPoint >= calScreen -> setMaxButton.setPoint) {
        calScreen -> setMaxButton.setPoint += 10;
        calScreen -> setMaxButton.update();
      }
      calScreen -> corr = 0;
      calScreen -> adjusting = 3;
      calScreen -> update();
      return;
    }
    if (calScreen -> zeroButton.touched(TouchX, TouchY)) {
      calScreen -> zeroing = 5;
      calScreen -> update();
      return;
    }
    if (calScreen -> setTempButton.touched(TouchX, TouchY)) {
      calScreen -> setTempButton.touchHandle(calScreen -> setTempButton.touched(TouchX, TouchY));
      calScreen -> newTemp = 1;
      return;
    }
    if (calScreen -> exitButton.touched(TouchX, TouchY)) {
      calScreen -> ~CalScreen();
      currentScreen = 0;
      mainScreen = new (memBufferMainScreen) MainScreen(board);
      mainScreen -> show();
      return;
    }
    if (calScreen -> envButton.touched(TouchX, TouchY)) {
      calScreen -> ~CalScreen();
      currentScreen = 2;
      envScreen = new (memBufferEnvScreen) EnvScreen(board);
      envScreen -> show();
      return;
    }
  }
  if (currentScreen == 2) { // EnvScreen
    if (envScreen -> exitButton.touched(TouchX, TouchY)) {
      envScreen -> ~EnvScreen();
      currentScreen = 1;
      calScreen = new (memBufferCalScreen) CalScreen(board);
      calScreen -> show();
      return;
    }
  }
  if (currentScreen == 3) { // Info
    if (infoScreen -> exitButton.touched(TouchX, TouchY)) {
      infoScreen -> ~InfoScreen();
      currentScreen = 0;
      mainScreen = new (memBufferMainScreen) MainScreen(board);
      mainScreen -> show();
      return;
    }
  }
}