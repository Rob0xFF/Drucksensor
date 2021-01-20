#include <board.h>

void Board::begin(void)
{
  pressureSensor.setAveraging(PMC_AVG_4);
  pressureSensor.setBridgeSensorAdaption(GAIN_14);
  pressureSensor.setBridgeMode(BSP_NEGATIVE);
	pressureSensor.setOutputIOConfiguration(ACOS1_MEASURAND, COS1_VOLTAGE, PMIO2_DISABLE, PMIO1_PWM1, ACOS2_MEASURAND);
	pressureSensor.start();
}

void Board::update(void)
{
	if(!extSerial.isBusy()) {
		pressureSensor.readOutput();
		float pressure = pressureSensor.getPressure();
		Serial.print(pressure / 1000.0F);
		Serial.print(" kPa ... ");
		Serial.print(pressure / 133.322F);
		Serial.println(" mmHg");
	}
}