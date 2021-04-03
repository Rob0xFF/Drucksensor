#ifndef PIDBOARD_h
#define PIDBOARD_h

#include "Arduino.h"
#include "Wire.h"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <pwmDevice.h>
#include <digitalDevice.h>
#include <PID_v1.h>

class Board
{
  public:

    Board()
    {
			Serial.begin(9600);
      _tempSensor.begin();
			updateTemperature();
  		Input = _temperature;
  		Setpoint = 27.0;
			_myPID.SetMode(AUTOMATIC);
    };

    void update();

  private:

     OneWire _oneWire = OneWire(7);
     DallasTemperature _tempSensor = DallasTemperature(&_oneWire);

    inline void updateTemperature()
    {
      _tempSensor.requestTemperatures();
      _temperature = _tempSensor.getTempCByIndex(0);
    };

    float _temperature = DEVICE_DISCONNECTED_C;

		PWMDevice IN1 = PWMDevice(5);
		PWMDevice IN2 = PWMDevice(6);

		double Setpoint, Input, Output;

		double Kp=2, Ki=5, Kd=1;
		PID _myPID = PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

};
#endif