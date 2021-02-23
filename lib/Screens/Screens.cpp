#include <Screens.h>

void ScreenHeader::show(void)
{
  //board.TFT.drawRect(0, 0, board.TFT.width(), board.TFT.height(), TFT_GRAY);
  board.TFT.setTextSize(1);
  board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
  board.TFT.setCursor(2, 1);
  board.TFT.print(F("ZSC31050 Calibration."));	
  board.TFT.setCursor(252, 1);
  board.TFT.print(F("10.0C 10.0"));
  board.TFT.setCursor(312,1);
  board.TFT.print((char) 37);
}

void ScreenHeader::update(void)
{
  board.TFT.setTextSize(1);
  board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
  if (temperature != board.temperature) {
    char oldTemp[5];
    strlcpy(oldTemp, tempStr, 5);
    temperature = board.temperature;
    char newTemp[5];
    dtostrf(temperature, 4, 1, newTemp);
    strlcpy(tempStr, newTemp, 5);
    board.TFT.updateCharArray(252, 1, oldTemp, newTemp, TFT_WHITE, TFT_GRAY, 1, 1);
  }
  if (humidity != board.humidity) {
    char oldHum[5];
    strlcpy(oldHum, humStr, 5);
    humidity = board.humidity;
    char newHum[5];
    dtostrf(humidity, 4, 1, newHum);
    strlcpy(humStr, newHum, 5);
    board.TFT.updateCharArray(288, 1, oldHum, newHum, TFT_WHITE, TFT_GRAY, 1, 1);
  }
}

void MainScreen::show(void)
{
	bridge.show();
	rawPressureBox.show();
	correctedPressureBox.show();
	rawTemperature1Box.show();
	adaptionButton.show();
	correctionButton.show();
	outputButton.show();
}

void MainScreen::update(void)
{
	bridge.update();
	rawPressureBox.update();
	correctedPressureBox.update();
	rawTemperature1Box.update();
}
