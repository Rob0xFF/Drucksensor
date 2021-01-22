#include <board.h>

void Board::begin(void)
{
  pressureSensor.setAveraging(PMC_AVG_4);
  pressureSensor.setBridgeSensorAdaption(GAIN_14);
  pressureSensor.setBridgeMode(BSP_NEGATIVE);
	pressureSensor.setOutputConfiguration(ACOS1_MEASURAND, COS1_VOLTAGE, ACOS2_MEASURAND, PMIO1_PWM1);
	pressureSensor.setPWM(PWMRES_11BIT, PWMD_1, PWMPO1_LOW);
	pressureSensor.start();
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.display();
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
	display.cp437(true);
}

void Board::update(void)
{
	if(!extSerial.isBusy()) {
		pressureSensor.readOutput();
		float pressure = pressureSensor.getPressure();
		display.clearDisplay();
		display.setCursor(10,10);
		display.print(pressure / 1000.0F);
		display.println(" kPa");
		display.print(pressure / 133.322F);
		display.println(" mmHg");
		display.display();
	}
}