#include <board.h>

void Board::begin(void)
{
  pressureSensor.setAveraging(PMC_AVG_4);
	pressureSensor.start();
}

void Board::update(void)
{
	if(!extSerial.isBusy()) {
		//pressureSensor.readOutput();
	}
}