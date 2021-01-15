#include <ZSC31050.h>

uint8_t ZSC31050::begin(void)
{
	return cmd(START_CYC_RAM);
}

void ZSC31050::readOutput(void)
{
	uint64_t readout = read48();
	_T2 = (uint16_t) (readout & 0xFFFFLL);
	_T1 = (uint16_t) ((readout & 0xFFFF0000LL) >> 16LL);
	_P = (uint16_t) ((readout & 0xFFFF00000000LL) >> 32LL);
}

float ZSC31050::getPressure(void)
{
	return _pressSlope * _P + _pressOffset;
}

float ZSC31050::getTemperature(void)
{
	return _tempSlope * _T1 + _tempOffset;
}

uint8_t ZSC31050::saveConfig(void)
{
	return cmd(COPY_RAM2EEP);
}

// ****** END of user functions ******* //

uint8_t ZSC31050::cmd(uint8_t cmd, uint16_t delay)
{
	Wire.beginTransmission(_i2cAddr);
  Wire.write(cmd);
  uint8_t retVal = Wire.endTransmission();
	delayMicroseconds(delay);
	return(retVal);
}

uint8_t ZSC31050::cmd(uint8_t cmd, uint16_t delay, uint8_t arg)
{
	Wire.beginTransmission(_i2cAddr);
  Wire.write(cmd);
	Wire.write(arg);
  uint8_t retVal = Wire.endTransmission();
	delayMicroseconds(delay);
	return(retVal);
}

uint8_t ZSC31050::cmd(uint8_t cmd, uint16_t delay, uint8_t arg1, uint8_t arg2)
{
	Wire.beginTransmission(_i2cAddr);
  Wire.write(cmd);
	Wire.write(arg1);
	Wire.write(arg2);
  uint8_t retVal = Wire.endTransmission();
	delayMicroseconds(delay);
	return(retVal);
}

uint8_t ZSC31050::read8(void)
{
	uint8_t retVal = 0;
	Wire.beginTransmission(_i2cAddr);
  Wire.requestFrom(_i2cAddr, (uint8_t) 1);
	retVal = Wire.read();
  return retVal;
}

uint16_t ZSC31050::read16(void)
{
	uint16_t retVal = 0;
	Wire.beginTransmission(_i2cAddr);
  Wire.requestFrom(_i2cAddr, (uint8_t) 2);
	retVal = Wire.read();
	retVal <<= 8;
	retVal |= Wire.read();
  return retVal;
}

uint32_t ZSC31050::read32(void)
{
	uint32_t retVal = 0;
	Wire.beginTransmission(_i2cAddr);
  Wire.requestFrom(_i2cAddr, (uint8_t) 4);
	retVal = Wire.read();
	retVal <<= 8L;
	retVal |= Wire.read();
	retVal <<= 8L;
	retVal |= Wire.read();
	retVal <<= 8L;
	retVal |= Wire.read();
  return retVal;
}

uint64_t ZSC31050::read48(void)
{
	uint64_t retVal = 0;
	Wire.beginTransmission(_i2cAddr);
  Wire.requestFrom(_i2cAddr, (uint8_t) 6);
	retVal = Wire.read();
	retVal <<= 8LL;
	retVal |= Wire.read();
	retVal <<= 8LL;
	retVal |= Wire.read();
	retVal <<= 8LL;
	retVal |= Wire.read();
	retVal <<= 8LL;
	retVal |= Wire.read();
	retVal <<= 8LL;
	retVal |= Wire.read();
  return retVal;
}