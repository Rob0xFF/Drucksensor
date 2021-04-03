#include <board.h>

void Board::update(void)
{
  updateTemperature();
	Serial.println(_temperature);
  Input = (double) _temperature;
  _myPID.Compute();
  IN1.setPWM(Output);
	Serial.println(Output);
}