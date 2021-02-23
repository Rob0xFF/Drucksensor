#include <board.h>

void Board::begin(void)
{
  pinMode(71, INPUT);
	if(digitalRead(71) == HIGH) {
		Serial.write(ACK);
    Serial.print("V2.05 ");
    Serial.write(AT);
    Serial.print(" ZMD AG 2004 - CB");
    Serial.write(CR);
    Serial.write(LF);
	}
	HIH.start();
  voltageSensor.begin();
  voltageSensor.configure(INA226_AVERAGES_128, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
  voltageSensor.calibrate(0.1, 0.1);
  TFT.begin();
	touchScreen.begin();
  TFT.setRotation(1);
  TFT.fillScreen(0x0000);
	pressureSensor.setMode(COMMAND_MODE);
}

void Board::update(void)
{
	if(!extSerial.isBusy()) {
  	HIH.update();
  	temperature = HIH.temperature();
  	humidity = HIH.humidity() * 100.0;
		bridgeVoltage = voltageSensor.readBusVoltage();
		voltage = voltageSensor.readShuntVoltage() * 1000.0;
		if(digitalRead(71) != HIGH) {
			rawP = pressureSensor.getRawPressure();
 			correctedP = pressureSensor.getCorrectedPressure();
			correctedP_SI = pressureSensor.getPressure();
			rawT1 = pressureSensor.getRawTemperature1();
		}
	}
}