#include <board.h>

void Board::update(void)
{
  updateTemperature();
  Input = (double) _temperature;
  _myPID.Compute();
	if(Output >= 0) {
		IN1.setPWM(Output);
		IN2.off();
	}
	else {
		IN2.setPWM(-Output);
		IN1.off();
	}
	elapsed++;
	counter--;
	if(counter == 0) {
		Serial.print(elapsed);
		Serial.print("; ");
		Serial.print(_temperature);
		Serial.print("; ");
		Serial.print(Output);
		Serial.print("; ");
		Serial.print(_myPID.GetDirection());
		Serial.println();
		counter = 10;
	}
}