#include <Screens.h>

void ScreenHeader::show(void)
{
  //board.TFT.drawRect(0, 0, board.TFT.width(), board.TFT.height(), TFT_GRAY);
  board.TFT.setTextSize(1);
  board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
  board.TFT.setCursor(2, 1);
  board.TFT.print(F("ZSC31050 Calibration"));
  board.TFT.setCursor(252, 1);
  board.TFT.print(F("10.0C 10.0"));
  board.TFT.setCursor(312, 1);
  board.TFT.print((char) 37);
}

void ScreenHeader::update(void)
{
  board.TFT.setTextSize(1);
  board.TFT.setTextColor(TFT_WHITE, TFT_BLACK);
  if (temperature != board.temperatureINT) {
    char oldTemp[5];
    strlcpy(oldTemp, tempStr, 5);
    temperature = board.temperatureINT;
    char newTemp[5];
    dtostrf(temperature, 4, 1, newTemp);
    strlcpy(tempStr, newTemp, 5);
    board.TFT.updateCharArray(252, 1, oldTemp, newTemp, TFT_WHITE, TFT_GRAY, 1, 1);
  }
  if (humidity != board.humidityINT) {
    char oldHum[5];
    strlcpy(oldHum, humStr, 5);
    humidity = board.humidityINT;
    char newHum[5];
    dtostrf(humidity, 4, 1, newHum);
    strlcpy(humStr, newHum, 5);
    board.TFT.updateCharArray(288, 1, oldHum, newHum, TFT_WHITE, TFT_GRAY, 1, 1);
  }
  if (board.isAvailable(USB_CONN)) {
    if (!board.extSerial.isConnected()) {
      board.TFT.fillRoundRect(200, 0, 30, 9, 4, TFT_BLUE);
    } else {
      board.TFT.fillRoundRect(200, 0, 30, 9, 4, TFT_GREEN);
    }
    board.TFT.setTextColor(TFT_BLACK);
    board.TFT.setCursor(206, 1);
    board.TFT.print(F("USB"));
  } else {
    board.TFT.fillRoundRect(200, 0, 30, 9, 4, TFT_RED);
    board.TFT.setTextColor(TFT_BLACK);
    board.TFT.setCursor(206, 1);
    board.TFT.print(F("USB"));
  }
  if (board.sensorStatus == INT) {
    board.TFT.fillRoundRect(200 - 10 * 6, 0, 9 * 6, 9, 4, TFT_GREEN);
    board.TFT.setTextColor(TFT_BLACK);
    board.TFT.setCursor(206 - 10 * 6, 1);
    board.TFT.print(F("INT SEN"));
  } else if (board.sensorStatus == EXT) {
    board.TFT.fillRoundRect(200 - 10 * 6, 0, 9 * 6, 9, 4, TFT_GREEN);
    board.TFT.setTextColor(TFT_BLACK);
    board.TFT.setCursor(206 - 10 * 6, 1);
    board.TFT.print(F("EXT SEN"));
  } else {
    board.TFT.fillRoundRect(200 - 10 * 6, 0, 9 * 6, 9, 4, TFT_RED);
    board.TFT.setTextColor(TFT_BLACK);
    board.TFT.setCursor(209 - 10 * 6, 1);
    board.TFT.print(F("NO SEN"));
  }
}

void MainScreen::show(void)
{
  bridge.show();
	senOutSIBox.show();
	senOutBox.show();
	senT1Box.show();
	senT2Box.show();
	idBox.show();
	tempBox.show();
	humBox.show();
	presBox.show();
  adaptionButton.show();
  correctionButton.show();
  outputButton.show();
}

void MainScreen::update(void)
{
  bridge.update();
	senOutSIBox.update();
	senOutBox.update();
	senT1Box.update();
	senT2Box.update();
	idBox.update();
	tempBox.update();
	presBox.update();
	humBox.update();
}
