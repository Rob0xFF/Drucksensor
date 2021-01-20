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
    * @brief set ZSC31050 bridge sensor adaption
    * @param Span: GAIN_420 (2mV/V), GAIN_280 (3mV/V), GAIN_210 (4mV/V), GAIN_140 (6mV/V), GAIN_105 (8mV/V), GAIN_70 (12mV/V), GAIN_52G5 (16mV/V), GAIN_35 (24mV/V), GAIN_26G25 (32mV/V), GAIN_14 (50mV/V), GAIN_9G3 (80mV/V), GAIN_7 (100mV/V), GAIN_2G8 (280mV/V)
    * @param ADC Range Shift P: ADRAPR_15_16 (15/16), ADRAPR_7_8 (7/8), ADRAPR_3_4 (3/4), ADRAPR_1_2 (1/2)
    * @param ADC Bit resolution: RADC_9BIT, RADC_10BIT, RADC_11BIT, RADC_12BIT, RADC_13BIT, RADC_14BIT, RADC_15BIT
    * @param ADC Order: OADC_1ST_ORDER, OADC_2ND_ORDER
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setBridgeSensorAdaption(CFGAFE_GAIN gain = GAIN_420, CFGAFE_ADRAPR rangeShift = ADRAPR_3_4, CFGAFE_RADC resolution = RADC_13BIT, CFGAFE_OADC order = OADC_2ND_ORDER);

    /*!
    * @brief set ZSC31050 bridge mode
    * @param bridge signal polarity: BSP_POSITIVE, BSP_NEGATIVE
    * @param bridge excitation mode: CSBE_VOLTAGE, CSBE_CURRENT
    * @param A/D converter reference voltage: ADREF_VBR, ADREF_VDDA
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setBridgeMode(CFGAPP_BSP polarity = BSP_POSITIVE, CFGAPP_CSBE excitationMode = CSBE_VOLTAGE, CFGAPP_ADREF refVoltage = ADREF_VBR);

    /*!
    * @brief set ZSC31050 output configuration
    * @param Selection of output via OUT pin: ACOS1_MEASURAND, ACOS1_TEMPERATURE1, ACOS1_TEMPERATURE2
    * @param output mode port OUT: COS1_VOLTAGE, COS1_PWM2, COS1_CURRENT,	COS1_DISABLE = 0b11
    * @param output mode port IO2: PMIO2_DISABLE, PMIO2_ALARM2
    * @param output mode port IO1: PMIO1_DISABLE, PMIO1_PWM1, PMIO1_ALARM1
    * @param Selection of output via IO1 pin (PWM), PWM at IO1 must be activated: ACOS2_MEASURAND, ACOS2_TEMPERATURE1, ACOS2_TEMPERATURE2
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setOutputConfiguration(CFGCYC_ACOS1 out = ACOS1_MEASURAND, CFGOUT_COS1 outMode = COS1_VOLTAGE, CFGOUT_PMIO2 IO2Mode = PMIO2_DISABLE, CFGOUT_PMIO1 IO1Mode = PMIO1_DISABLE, CFGCYC_ACOS2 IO1 = ACOS2_TEMPERATURE1);

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

    float _pressSlope = 1.2129015F;

    float _pressOffset = -1.552121F;

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