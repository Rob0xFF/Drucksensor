#include <board.h>

void Board::begin(void)
{
  Serial.write(0x06);
  Serial.print("V2.05 ");
  Serial.write(0xA9);
  Serial.print(" ZMD AG 2004 - CB");
  Serial.write(0x0D);
  Serial.write(0x0A);
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
    multiplexer.disable();
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
//     if(mpr.begin()) {
// 			TFT.setTextColor(0xF000);
//     	TFT.println(F("FAIL"));
//     	TFT.println(F("> > Check on-board connections!"));
//     	return;
// 		}
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
  TFT.setTextColor(0xFFFF);
  TFT.print(F("> MCP4725 DAC"));
  TFT.setCursor(TFT.width() - 4 * 6, TFT.getCursorY());
  Wire.beginTransmission(I2C_MCP4725);
  if (!Wire.endTransmission()) {
    available(MCP4725);
    dac.begin(I2C_MCP4725);
    dac.setVoltage(0, false);
    TFT.setTextColor(0x0FF0);
    TFT.println(F("DONE"));
  } else {
    TFT.setTextColor(0xF000);
    TFT.println(F("FAIL"));
    TFT.println(F("> > Check on-board connections!"));
    return;
  }
  //uint16_t zero = 0;
  //EEPROM.put(0, zero);
  TFT.println();
  TFT.setTextColor(0xFFFF, 0x0000);
  TFT.println();
  _delay_ms(1000);
  uint16_t _myX = TFT.width() / 2 - 55;
  uint16_t _myY = TFT.getCursorY() + 10;
  TFT.drawLine(_myX + 53, _myY + 0, _myX + 0, _myY + 53, 0xFFFF);
  TFT.drawLine(_myX + 53, _myY + 1, _myX + 1, _myY + 53, 0xFFFF);
  TFT.drawLine(_myX + 54, _myY + 0, _myX + 107, _myY + 53, 0xFFFF);
  TFT.drawLine(_myX + 54, _myY + 1, _myX + 107, _myY + 54, 0xFFFF);
  TFT.drawLine(_myX + 1, _myY + 54, _myX + 54, _myY + 107, 0xFFFF);
  TFT.drawLine(_myX + 2, _myY + 54, _myX + 54, _myY + 106, 0xFFFF);
  TFT.drawLine(_myX + 55, _myY + 106, _myX + 106, _myY + 55, 0xFFFF);
  TFT.drawLine(_myX + 55, _myY + 105, _myX + 106, _myY + 54, 0xFFFF);
  TFT.drawLine(_myX + 54, _myY + 105, _myX + 105, _myY + 54, 0xFFFF);
  TFT.drawLine(_myX + 54, _myY + 104, _myX + 105, _myY + 53, 0xFFFF);
  TFT.drawLine(_myX + 53, _myY + 104, _myX + 104, _myY + 53, 0xFFFF);
  TFT.drawLine(_myX + 53, _myY + 103, _myX + 104, _myY + 52, 0xFFFF);
  TFT.drawLine(_myX + 36, _myY + 19, _myX + 71, _myY + 19, 0xFFFF);
  TFT.drawLine(_myX + 33, _myY + 84, _myX + 71, _myY + 84, 0xFFFF);
  TFT.drawLine(_myX + 32, _myY + 83, _myX + 72, _myY + 83, 0xFFFF);
  TFT.drawLine(_myX + 31, _myY + 82, _myX + 73, _myY + 82, 0xFFFF);
  TFT.drawLine(_myX + 32, _myY + 81, _myX + 74, _myY + 81, 0xFFFF);
  TFT.drawLine(_myX + 32, _myY + 80, _myX + 75, _myY + 80, 0xFFFF);
  TFT.drawLine(_myX + 35, _myY + 79, _myX + 73, _myY + 21, 0xFFFF);
  TFT.drawLine(_myX + 34, _myY + 79, _myX + 72, _myY + 21, 0xFFFF);
  TFT.drawLine(_myX + 33, _myY + 79, _myX + 72, _myY + 20, 0xFFFF);
  _delay_ms(3000);
  TFT.fillScreen(0x0000);
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
    if (sensorStatus == EXT) {
      multiplexer.disable();
      multiplexer.enableChannel(0);
    }
    HIHINT.update();
    humidityINT = HIHINT.humidity() * 100.0;
    temperatureINT = HIHINT.temperature();
    bridgeVoltageINT = voltageSensorINT.readBusVoltage();
    voltageINT = voltageSensorINT.readShuntVoltage() * 1000.0;
    mprPres = mpr.readPressure();
		mprPresRelative = mprPres - mprPresZero;
    if (sensorStatus == EXT) {
      multiplexer.disable();
      multiplexer.enableChannel(1);
      HIHEXT -> update();
      humidityEXT = HIHEXT -> humidity() * 100.0;
      temperatureEXT = HIHEXT -> temperature();
      bridgeVoltageEXT = voltageSensorEXT -> readBusVoltage();
      voltageEXT = voltageSensorEXT -> readShuntVoltage() * 1000.0;
      senTemperature = temperatureEXT;
      senHumidity = humidityEXT;
      senBridgeVoltage = bridgeVoltageEXT;
      senVoltage = voltageEXT;
      senChipID = chipIDEXT;
      senSlope = slopeEXT;
      senOffset = offsetEXT;
      extSerial.senChipID = chipIDEXT;
      if (!extSerial.isConnected() && zscEXT != nullptr) {
        //P = zscEXT -> getCorrectedPressure();
        //T1 = zscEXT -> getCorrectedT1();
        //T2 = zscEXT -> getCorrectedT2();
        P_SI = (senSlope * (float) P + senOffset) / 100;
      }
    }
    if (sensorStatus == INT) {
      senTemperature = temperatureINT;
      senHumidity = humidityINT;
      senBridgeVoltage = bridgeVoltageINT;
      senVoltage = voltageINT;
      senChipID = chipIDINT;
      senSlope = slopeINT;
      senOffset = offsetINT;
      extSerial.senChipID = chipIDINT;
      if (!extSerial.isConnected() && zscINT != nullptr) {
        //P = zscINT -> getCorrectedPressure();
        //T1 = zscINT -> getCorrectedT1();
        //T2 = zscINT -> getCorrectedT2();
        P_SI = (senSlope * (float) P + senOffset) / 100;
      }
    }
  }
}

void Board::checkEXT(void)
{
  multiplexer.disable();
  multiplexer.enableChannel(0);
  Wire.beginTransmission(I2C_ZSC31050);
  if (!Wire.endTransmission()) {
    if (!isAvailable(ZSC31050_INT)) {
      available(ZSC31050_INT);
      zscINT = new (memBufferZscINT) ZSC31050(I2C_ZSC31050);
      zscINT -> setMode(COMMAND_MODE);
      chipIDINT = zscINT -> getRegister(USR_VAL1);
      const float ZERO = 0.0F;
      if (chipIDINT == 0) { // new chip
        uint16_t latestID;
        EEPROM.get(0, latestID);
        chipIDINT = (latestID + 1) % 511;
        zscINT -> setRegister(USR_VAL1, chipIDINT, TO_EEPROM);
        EEPROM.put(0, chipIDINT);
        EEPROM.put(chipIDINT * 8, ZERO);
        EEPROM.put(chipIDINT * 8 + 4, ZERO);
      }
      EEPROM.get(chipIDINT * 8, slopeINT);
      EEPROM.get(chipIDINT * 8 + 4, offsetINT);
      sensorStatus = INT;
    }
  } else {
    if (isAvailable(ZSC31050_INT) && zscINT != nullptr) {
      unAvailable(ZSC31050_INT);
      zscINT -> ~ZSC31050();
      sensorStatus = UNKNOWN;
    }
  }
  multiplexer.disable();
  multiplexer.enableChannel(1);
  Wire.beginTransmission(I2C_ZSC31050);
  if (!Wire.endTransmission()) {
    if (!isAvailable(ZSC31050_EXT)) {
      available(ZSC31050_EXT);
      zscEXT = new (memBufferZscEXT) ZSC31050(I2C_ZSC31050);
      zscEXT -> setMode(COMMAND_MODE);
      chipIDEXT = zscEXT -> getRegister(USR_VAL1);
      const float ZERO = 0.0F;
      if (chipIDEXT == 0) { // new chip
        uint16_t latestID;
        EEPROM.get(0, latestID);
        chipIDEXT = (latestID + 1) % 511;
        zscEXT -> setRegister(USR_VAL1, chipIDEXT, TO_EEPROM);
        EEPROM.put(0, chipIDEXT);
        EEPROM.put(chipIDEXT * 8, ZERO);
        EEPROM.put(chipIDEXT * 8 + 4, ZERO);
      }
      EEPROM.get(chipIDEXT * 8, slopeEXT);
      EEPROM.get(chipIDEXT * 8 + 4, offsetEXT);
      voltageSensorEXT = new (memBufferVoltageSensorEXT) INA226();
      voltageSensorEXT -> begin();
      voltageSensorEXT -> configure(INA226_AVERAGES_128, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
      voltageSensorEXT -> calibrate(0.1, 0.1);
      HIHEXT = new (memBufferHIHEXT) HIH61XX(I2C_HIH6130, 255);
      HIHEXT -> start();
      sensorStatus = EXT;
    }
  } else {
    if (isAvailable(ZSC31050_EXT) && zscEXT != nullptr) {
      unAvailable(ZSC31050_EXT);
      zscEXT -> ~ZSC31050();
      sensorStatus = UNKNOWN;
    }
  }
  multiplexer.disable();
  switch (sensorStatus) {
    case INT:
      multiplexer.enableChannel(0);
      break;
    case EXT:
      multiplexer.enableChannel(1);
      break;
    case UNKNOWN:
      multiplexer.enableChannel(0);
      break;
    default:
      multiplexer.disable();
      break;
  }
}

