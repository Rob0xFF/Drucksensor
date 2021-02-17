#include <board.h>

void Board::begin(void)
{
	HIH.start();
  voltageSensor.begin();
  voltageSensor.configure(INA226_AVERAGES_128, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
  voltageSensor.calibrate(0.1, 0.1);
  TFT.begin();
	touchScreen.begin();
  TFT.setRotation(1);
  TFT.fillScreen(0x0000);
}

void Board::update(void)
{
  HIH.update();
  temperature = HIH.temperature();
  humidity = HIH.humidity() * 100.0;
  pressureSensor.readOutput();
 	pressureSI = pressureSensor.getPressure();
 	rawPressure = pressureSensor.getRawPressure();
	bridgeVoltage = voltageSensor.readBusVoltage();
	voltage = voltageSensor.readShuntVoltage() * 1000.0;
}