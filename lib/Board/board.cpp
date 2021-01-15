#include <board.h>

void Board::begin(void)
{
  pressureSensor.begin();
}

void Board::update(void)
{
	if(!extSerial.isBusy()) {
		pressureSensor.readOutput();
	}
}