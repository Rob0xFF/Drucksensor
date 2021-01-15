#ifndef ZSC31050_h
#define ZSC31050_h

#include "Arduino.h"
#include "Wire.h"
#include <EEPROM.h>
#include "ZSC31050Registers.h"

class ZSC31050
{
  public:

    ZSC31050(uint8_t i2cAddr) : _i2cAddr(i2cAddr)
    {
			cmd(START_CM);
			cmd(CFG_SIF_TO_I2C);
    };

		uint8_t begin(void);

    void readOutput(void);

    float getPressure(void);

    float getTemperature(void);

		uint8_t saveConfig(void);

  private:

		uint8_t _i2cAddr;

    uint16_t _P;

    uint16_t _T1;

    uint16_t _T2;

    float _pressSlope = 1;

    float _pressOffset = 0;

    float _tempSlope = 1;

    float _tempOffset = 0;

		uint8_t cmd(uint8_t cmd, uint16_t delay);
		uint8_t cmd(uint8_t cmd, uint16_t delay, uint8_t arg);
		uint8_t cmd(uint8_t cmd, uint16_t delay, uint8_t arg1, uint8_t arg2);

		uint8_t read8(void);
		uint16_t read16(void);
		uint32_t read32(void);
		uint64_t read48(void);

};
#endif