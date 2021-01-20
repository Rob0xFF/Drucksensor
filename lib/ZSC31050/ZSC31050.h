#ifndef ZSC31050_h
#define ZSC31050_h

#include "Arduino.h"
#include "Wire.h"
#include <EEPROM.h>
#include "ZSC31050Registers.h"
#include "ZSC31050Configuration.h"

class ZSC31050
{
  public:

    /*!
    * @brief ZSC31050 class constructor
    * @param I2C address of the ZSC31050
    */
    ZSC31050(uint8_t i2cAddr) : _i2cAddr(i2cAddr)
    {
      setMode(COMMAND_MODE);
      cmd(CFG_SIF_TO_I2C);
    };

    /*!
    * @brief start ZSC31050 measurement cycle
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return 1 - data too long to fit in transmit buffer
    * @return 2 - received NACK on transmit of address
    * @return 3 - received NACK on transmit of data
    * @return 4 - other error
    */
    uint8_t start(void);

    /*!
    * @brief set ZSC31050 count of bridge measurements per cycle (averaging)
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return 1 - data too long to fit in transmit buffer
    * @return 2 - received NACK on transmit of address
    * @return 3 - received NACK on transmit of data
    * @return 4 - other error
    */
    uint8_t setAveraging(CFGCYC_PMC avg);

    /*!
    * @brief read ZSC31050 output register and store values to _P, _T1, _T2
    */
    void readOutput(void);

    /*!
    * @brief get pressure in SI unit (Pascal)
    * @return pressure in Pascal
    */
    float getPressure(void);

    /*!
    * @brief get temperature in °C
    * @return temperature in °C
    */
    float getTemperature(void);

    /*!
    * @brief reverse bridge polarity
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return 1 - data too long to fit in transmit buffer
    * @return 2 - received NACK on transmit of address
    * @return 3 - received NACK on transmit of data
    * @return 4 - other error
    */
    uint8_t setBridgePolarity();

    /*!
    * @brief set DAC Output to desired value
    * @param DAC value [0, 0x7FF]
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return 1 - data too long to fit in transmit buffer
    * @return 2 - received NACK on transmit of address
    * @return 3 - received NACK on transmit of data
    * @return 4 - other error
    */
    uint8_t forceDACOutput(uint16_t val);

    /*!
    * @brief set working mode of the ZSC31050
    * @param one of the three working modes defined in Mode
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return 1 - data too long to fit in transmit buffer
    * @return 2 - received NACK on transmit of address
    * @return 3 - received NACK on transmit of data
    * @return 4 - other error
    * @return 5 - tried to switch from normal mode to command or open mode (the device is stuck into normal mode once started)
    */
    uint8_t setMode(Mode mode);

    /*!
    * @brief safe current configuration (RAM -> EEPROM)k
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return 1 - data too long to fit in transmit buffer
    * @return 2 - received NACK on transmit of address
    * @return 3 - received NACK on transmit of data
    * @return 4 - other error
    */
    uint8_t saveConfig(void);

  private:

    uint8_t _i2cAddr;

    Mode _mode;

    uint16_t _P;

    uint16_t _T1;

    uint16_t _T2;

    float _pressSlope = 1;

    float _pressOffset = 0;

    float _tempSlope = 1;

    float _tempOffset = 0;

    uint8_t cmd(uint8_t cmd, uint16_t delay);
    uint8_t cmd(uint8_t cmd, uint16_t delay, uint16_t arg);

    template <typename cfgType> uint8_t cfg(uint8_t addr, uint16_t mask, cfgType val);

    uint8_t read8(void);
    uint16_t read16(void);
    uint32_t read32(void);
    uint64_t read48(void);

    uint16_t FSB16(uint16_t val);

};
#endif