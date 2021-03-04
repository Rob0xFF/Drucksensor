#include <board.h>

void Board::begin(void)
{
  Serial.write(ACK);
  Serial.print("V2.05 ");
  Serial.write(AT);
  Serial.print(" ZMD AG 2004 - CB");
  Serial.write(CR);
  Serial.write(LF);
  pinMode(USB_PIN, INPUT_PULLUP);
  Wire.begin();
  TFT.begin();
  TFT.setRotation(1);
  TFT.fillScreen(0x0000);
  TFT.setCursor(0, 0);
  TFT.setTextColor(0xFFFF);
  TFT.setTextSize(1);
  TFT.println();
  TFT.println(F("ZSC31050 calibration device starting"));
  TFT.println();
  TFT.println();
  TFT.print(F("> TCA Multiplexer"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_TCA);
  if (!Wire.endTransmission()) {
    available(TCA);
    for (uint8_t i = 0; i < 8; i++) {
      multiplexer.disableChannel(i);
    }
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > Check on-board connections!"));
    return;
  }
  TFT.setTextColor(0xFFFF);
  multiplexer.enableChannel(0);
  TFT.print(F("> INA226 voltmeter (INT)"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_INA226);
  if (!Wire.endTransmission()) {
    available(INA226_INT);
    voltageSensorINT.begin();
    voltageSensorINT.configure(INA226_AVERAGES_128, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
    voltageSensorINT.calibrate(0.1, 0.1);
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > Check on-board connections!"));
    return;
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> HIH6130 monitor (INT)"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_HIH6130);
  if (!Wire.endTransmission()) {
    available(HIH6130_INT);
    HIHINT.start();
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > Check on-board connections!"));
    return;
  }
  multiplexer.disableChannel(0);
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> MPRLS pressure sensor"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_MPRLS);
  if (!Wire.endTransmission()) {
    available(MPRLS);
    mpr.begin();
    mprPresRef = mpr.readPressure();
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > Check on-board connections!"));
    return;
  }
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> FT6206 touch sensor"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_FT6206);
  if (!Wire.endTransmission()) {
    available(FT6206);
    touchScreen.begin();
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > Check on-board connections!"));
    return;
  }
  TFT.println();
  TFT.setTextColor(0xFFFF, 0x0000);
  TFT.println();
  TFT.println(F("Here is, what the cow says:"));
  TFT.println();
  _delay_ms(1000);
  // That's what the cow says.
  TFT.println(F("   ----------------------------------"));
  TFT.println(F(" < Great dude. Starting in 8 seconds. >"));
  TFT.println(F("   ----------------------------------"));
  TFT.println(F("          \\   ^__^ "));
  TFT.println(F("           \\  (oo)\\_______"));
  TFT.println(F("              (__)\\       )\\/\\"));
  TFT.println(F("                  ||----w |"));
  TFT.print(F("                  ||     ||"));
  TFT.setCursor(TFT.getCursorX(), TFT.getCursorY() - 8 * 6);
  _delay_ms(1000);
  TFT.print("7");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("6");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("5");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("4");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("3");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("2");
  TFT.setCursor(TFT.getCursorX() - 6, TFT.getCursorY());
  _delay_ms(1000);
  TFT.print("1");
  // TODO: check external RS232
  _delay_ms(1000);
  TFT.fillScreen(0x0000);
// 	pressureSensor.setMode(COMMAND_MODE);
// 	if(getChipID() == 0) {
// 		setChipID(0xEEEE);
// 	}
}

void Board::update(void)
{
  if (digitalRead(USB_PIN) == LOW) {
    available(USB_CONN);
  } else {
    if (extSerial.isConnected()) {
      extSerial.disConnect();
    }
    unAvailable(USB_CONN);
  }
  if (!extSerial.isBusy()) {
    if (!extSerial.isConnected()) {
      checkEXT();
    }
    if (sensorStatus == INT) {
      HIHINT.update();
      temperature = HIHINT.temperature();
      humidity = HIHINT.humidity() * 100.0;
      bridgeVoltage = voltageSensorINT.readBusVoltage();
      voltage = voltageSensorINT.readShuntVoltage() * 1000.0;
      mprPres = mpr.readPressure();
      mprPresDiff = 100.0 * (mprPres - mprPresRef);
      if (!extSerial.isConnected() && zscINT != nullptr) {
        correctedP = zscINT -> getCorrectedPressure();
      }
    }
  }
}

void Board::checkEXT(void)
{
  for (uint8_t i = 0; i < 2; i++) {
    multiplexer.disableChannel(i);
  }
  multiplexer.enableChannel(0);
  Wire.beginTransmission(I2C_ZSC31050);
  if (!Wire.endTransmission()) {
    if (!isAvailable(ZSC31050_INT) && !isAvailable(ZSC31050_EXT)) {
      available(ZSC31050_INT);
      zscINT = new (memBufferZscINT) ZSC31050(I2C_ZSC31050);
      zscINT -> setMode(COMMAND_MODE);
      zscINT -> setRegister(USR_VAL1, 0x00, TO_EEPROM);
      delay(200);
      chipIDINT = zscINT -> getRegister(USR_VAL1);
      if (chipIDINT == 0) {
        float f = 0.0f;
        for (uint16_t eeAddress = 8; eeAddress <= 4095; eeAddress += 2 * sizeof(float)) {
          EEPROM.get(eeAddress, f);
          if (isnan(f)) {
            chipIDINT = eeAddress / (2 * sizeof(float));
            zscINT -> setRegister(USR_VAL1, chipIDINT, TO_EEPROM);
            break;
          }
        }
      }
      sensorStatus = INT;
    }
  } else {
    if (isAvailable(ZSC31050_INT) && zscINT != nullptr) {
      unAvailable(ZSC31050_INT);
      zscINT -> ~ZSC31050();
      sensorStatus = UNKNOWN;
    }
  }
  multiplexer.disableChannel(0);
  multiplexer.enableChannel(1);
  Wire.beginTransmission(I2C_ZSC31050);
  if (!Wire.endTransmission()) {
    if (!isAvailable(ZSC31050_EXT)) {
      available(ZSC31050_EXT);
      zscEXT = new (memBufferZscEXT) ZSC31050(I2C_ZSC31050);
      chipIDEXT = zscEXT -> getRegister(USR_VAL1);
      if (chipIDEXT == 0) {
        float f = 0.0f;
        for (uint16_t eeAddress = 0; eeAddress <= 4095; eeAddress += 2 * sizeof(float)) {
          EEPROM.get(eeAddress, f);
          if (f == 0.0f) {
            chipIDINT = eeAddress / 2 * sizeof(float);
            zscEXT -> setRegister(USR_VAL1, chipIDEXT, TO_EEPROM);
          }
        }
      }
      sensorStatus = EXT;
    }
  } else {
    if (isAvailable(ZSC31050_EXT) && zscEXT != nullptr) {
      unAvailable(ZSC31050_EXT);
      zscEXT -> ~ZSC31050();
      if (!isAvailable(ZSC31050_INT)) {
        sensorStatus = UNKNOWN;
      } else {
        sensorStatus = INT;
      }
    }
  }
  multiplexer.disableChannel(1);
  switch (sensorStatus) {
    case INT:
      multiplexer.enableChannel(0);
      break;
    case EXT:
      multiplexer.enableChannel(1);
      break;
    default:
      break;
  }
}

// uint8_t Board::setChipID(uint16_t chipID)
// {
// 	//return pressureSensor.setRegister(USR_VAL1, chipID, EEPROM);
// }
