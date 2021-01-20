#include <ZSC31050.h>

uint8_t ZSC31050::start(void)
{
  return cmd(START_CYC_RAM);
}

uint8_t ZSC31050::setAveraging(CFGCYC_PMC avg)
{
  return cfg<CFGCYC_PMC>(CFGCYC, CFGCYC_PMC_MASK, avg);
}

uint8_t ZSC31050::setBridgeSensorAdaption(CFGAFE_GAIN gain, CFGAFE_ADRAPR rangeShift, CFGAFE_RADC resolution, CFGAFE_OADC order)
{
  uint8_t retVal = 0;
  retVal += cfg<CFGAFE_GAIN>(CFGAFE, CFGAFE_GAIN_MASK, gain);
  retVal += cfg<CFGAFE_ADRAPR>(CFGAFE, CFGAFE_ADRAPR_MASK, rangeShift);
  retVal += cfg<CFGAFE_RADC>(CFGAFE, CFGAFE_RADC_MASK, resolution);
  retVal += cfg<CFGAFE_OADC>(CFGAFE, CFGAFE_OADC_MASK, order);
  return retVal;
}

uint8_t ZSC31050::setBridgeMode(CFGAPP_BSP polarity, CFGAPP_CSBE excitationMode, CFGAPP_ADREF refVoltage)
{
  uint8_t retVal = 0;
  retVal += cfg<CFGAPP_BSP>(CFGAPP, CFGAPP_BSP_MASK, polarity);
  retVal += cfg<CFGAPP_CSBE>(CFGAPP, CFGAPP_CSBE_MASK, excitationMode);
  retVal += cfg<CFGAPP_ADREF>(CFGAPP, CFGAPP_ADREF_MASK, refVoltage);
  return retVal;
}

uint8_t ZSC31050::setOutputConfiguration(CFGCYC_ACOS1 out, CFGOUT_COS1 outMode, CFGOUT_PMIO2 IO2Mode, CFGOUT_PMIO1 IO1Mode, CFGCYC_ACOS2 IO1)
{
  uint8_t retVal = 0;
  retVal += cfg<CFGCYC_ACOS1>(CFGCYC, CFGCYC_ACOS1_MASK, out);
  retVal += cfg<CFGOUT_COS1>(CFGOUT, CFGOUT_COS1_MASK, outMode);
  retVal += cfg<CFGOUT_PMIO2>(CFGOUT, CFGOUT_PMIO2_MASK, IO2Mode);
  retVal += cfg<CFGOUT_PMIO1>(CFGOUT, CFGOUT_PMIO1_MASK, IO1Mode);
  retVal += cfg<CFGCYC_ACOS2>(CFGCYC, CFGCYC_ACOS2_MASK, IO1);
  return retVal;
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

uint8_t ZSC31050::forceDACOutput(uint16_t val)
{
  val = max(val, 0x7FF);
  return cmd(SET_DAC, val);
}

uint8_t ZSC31050::setMode(Mode mode)
{
  switch (mode) {
    case OPEN_MODE:
      if (_mode != NORMAL_MODE) {
        _mode = OPEN_MODE;
        return cmd(START_OM);
      } else {
        return 5;
      }
    case NORMAL_MODE:
      _mode = NORMAL_MODE;
      return cmd(START_NOM);
    case COMMAND_MODE:
      if (_mode != NORMAL_MODE) {
        _mode = COMMAND_MODE;
        return cmd(START_CM);
      } else {
        return 5;
      }
    default:
      return 4;
  }
}

uint8_t ZSC31050::saveConfig(void)
{
  uint8_t retVal = cmd(COPY_RAM2EEP);
  delay(500);
  return ;
}

// ****** END of user functions ******* //

uint8_t ZSC31050::cmd(uint8_t cmd, uint16_t delay)
{
  Wire.beginTransmission(_i2cAddr);
  Wire.write(cmd);
  uint8_t retVal = Wire.endTransmission();
  delayMicroseconds(delay);
  return (retVal);
}

uint8_t ZSC31050::cmd(uint8_t cmd, uint16_t delay, uint16_t arg)
{
  Wire.beginTransmission(_i2cAddr);
  Wire.write(cmd);
  Wire.write((uint8_t) (arg >> 8));
  Wire.write((uint8_t) arg);
  uint8_t retVal = Wire.endTransmission();
  delayMicroseconds(delay);
  return (retVal);
}

template <typename cfgType> uint8_t ZSC31050::cfg(uint8_t addr, uint16_t mask, cfgType val)
{
  cmd(addr + READ_RAM_OFFS, READ_RAM_DELAY);
  return cmd(addr + WRITE_RAM_OFFS, WRITE_RAM_DELAY, (read16() & ~mask) | val);
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