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
//      setInterface(I2C);
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
    * @brief set ZSC31050 advanced bridge sensor adaption
    * @brief enable extended zero compensation: XZCE_DISABLED, XZCE_ENABLED
    * @param eXtendedZeroCompensation value / polarity: XZC_POLARITY_POSITIVE, XZC_POLARITY_NEGATIVE
    * @param eXtendedZeroCompensation value / value: [XZC_0 ... XZC_31]
    * @param ADC range shift regarding signal from IN3 (TEMP2): ADRAIN3_15_16, ADRAIN3_7_8, ADRAIN3_3_4, ADRAIN3_1_2
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setAdvancedBridgeSensorAdaption(CFGAPP_XZCE state = XZCE_DISABLED, CFGAFE_XZC_POLARITY polarity = XZC_POLARITY_POSITIVE, CFGAFE_XZC value = XZC_0, CFGAPP_ADRAIN3 rangeShift = ADRAIN3_1_2);

    /*!
    * @brief set ZSC31050 bridge mode
    * @param bridge signal polarity: BSP_POSITIVE, BSP_NEGATIVE
    * @param bridge excitation mode: CSBE_VOLTAGE, CSBE_CURRENT
    * @param A/D converter reference voltage: ADREF_VBR, ADREF_VDDA
    * @param Adjust sensor bridge current factor (F): CSB_0F5,  CSB_0F625,  CSB_0F75,  CSB_0F875,  CSB_1F0,  CSB_1F125,  CSB_1F25,  CSB_1F375
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setBridgeMode(CFGAPP_BSP polarity = BSP_POSITIVE, CFGAPP_CSBE excitationMode = CSBE_VOLTAGE, CFGAPP_ADREF refVoltage = ADREF_VBR, ADJREF_CSB current = CSB_1F0);

    /*!
    * @brief set ZSC31050 temperature sensor adaption T1
    * @param Temperature 1 (T1) acquisition mode: TAM1_INT_DIODE, TAM1_EXT_DIODE, TAM1_EXT_RES
    * @param Gain analog front end temperature 1 meas.: GAINT1_4, GAINT1_3, GAINT1_2, GAINT1_1
    * @param ZSC31050 Temperature 1 (T1) zero-point adjust: ZCT1_0, ZCT1_1, ZCT1_2, ZCT1_3, ZCT1_4, ZCT1_5, ZCT1_6, ZCT1_7
    * @param Polarity of external temperature sensor for temperature 1 measurement: PETS1_VSS, PETS1_VDDA
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setTempSensorAdaptionT1(CFGTMP_TAM1 senType = TAM1_INT_DIODE, CFGTMP_GAINT1 gain = GAINT1_4, CFGTMP_ZCT1 zeroPointAdj = ZCT1_2, CFGTMP_PETS1 polarity = PETS1_VSS);

    /*!
    * @brief set ZSC31050 temperature sensor adaption T2
    * @param enable Temperature2 measurement: T2E_ENABLED, T2E_DISABLED
    * @param Temperature 2 (T2) acquisition mode: TAM2_INT_DIODE, TAM2_EXT_DIODE, TAM2_EXT_RES, TAM2_EXT_VOLT
    * @param Gain analog front end temperature 2 meas.: GAINT2_4, GAINT2_3, GAINT2_2, GAINT2_1
    * @param ZSC31050 Temperature 2 (T2) zero-point adjust: ZCT2_0, ZCT2_1, ZCT2_2, ZCT2_3, ZCT2_4, ZCT2_5, ZCT2_6, ZCT2_7
    * @param Polarity of external temperature sensor for temperature 2 measurement: PETS2_VSS, PETS2_VDDA
    * @param IN3 reference mode: IN3M_BANDGAP, IN3M_VDDA_2, IN3M_SUPPLY_VOLTAGE_CHECK
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setTempSensorAdaptionT2(CFGCYC_T2E state = T2E_DISABLED, CFGTMP_TAM2 senType = TAM2_INT_DIODE, CFGTMP_GAINT2 gain = GAINT2_4, CFGTMP_ZCT2 zeroPointAdj = ZCT2_2, CFGTMP_PETS2 polarity = PETS2_VSS, CFGAPP_IN3M mode = IN3M_VDDA_2);

    /*!
    * @brief set ZSC31050 output configuration
    * @param Selection of output via OUT pin: ACOS1_MEASURAND, ACOS1_TEMPERATURE1, ACOS1_TEMPERATURE2
    * @param output mode port OUT: COS1_VOLTAGE, COS1_PWM2, COS1_CURRENT,	COS1_DISABLE
    * @param Selection of output via IO1 pin (PWM), PWM at IO1 must be activated: ACOS2_MEASURAND, ACOS2_TEMPERATURE1, ACOS2_TEMPERATURE2
    * @param output mode port IO1: PMIO1_DISABLE, PMIO1_PWM1, PMIO1_ALARM1
    * @param output mode port IO2: PMIO2_DISABLE, PMIO2_ALARM2
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setOutputConfiguration(CFGCYC_ACOS1 out = ACOS1_MEASURAND, CFGOUT_COS1 outMode = COS1_VOLTAGE, CFGCYC_ACOS2 IO1 = ACOS2_TEMPERATURE1, CFGOUT_PMIO1 IO1Mode = PMIO1_DISABLE, CFGOUT_PMIO2 IO2Mode = PMIO2_DISABLE);

    /*!
    * @brief set ZSC31050 PWM configuratiom
    * @param Resolution PWM output: PWMRES_9BIT, PWMRES_10BIT, PWMRES_11BIT, PWMRES_12BIT
    * @param PWM CLK divider: PWMD_1, PWMD_2, PWMD_4, PWMD_8
    * @param PWM1 polarity: PWMPO1_HIGH, PWMPO1_LOW
    * @param PWM2 polarity: PWMPO2_HIGH, PWMPO2_LOW
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setPWM(CFGOUT_PWMRES resolution = PWMRES_11BIT, CFGOUT_PWMD divider = PWMD_1, CFGOUT_PWMPO1 polarity1 = PWMPO1_HIGH, CFGOUT_PWMPO2 polarity2 = PWMPO2_HIGH);

    /*!
    * @brief set ZSC31050 alarm settings
    * @param Enable Alarm window mode: AWME_DISABLED, AWME_ENABLED
    * @param alarm1 polarity: APO1_LOW_ACTIVE, APO1_HIGH_ACTIVE
    * @param alarm2 polarity: APO2_LOW_ACTIVE, APO2_HIGH_ACTIVE
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setAlarm(CFGOUT_AWME windowMode = AWME_DISABLED, CFGOUT_APO1 polarity1 = APO1_HIGH_ACTIVE, CFGOUT_APO2 polarity2 = APO2_HIGH_ACTIVE);

    /*!
    * @brief set ZSC31050 application and adjustment
    * @param analog voltage control (internal controller /w external transistor): VDCE_DISABLED, VDCE_ENABLED
    * @param VDDA controlled voltage: VDC_3V0, VDC_4V0, VDC_5V0, VDC_5V5
    * @param Fine adjustment of controlled analog supply voltage (percent - P): VDCA_M1P0, VDCA_M0P75, VDCA_M0P5, VDCA_M0P25, VDCA_0P0, VDCA_0P25, VDCA_0P5, VDCA_0P75
    * @param Count of bridge measurements per cycle (averaging): PMC_AVG_1, PMC_AVG_2, PMC_AVG_4, PMC_AVG_8, PMC_AVG_16, PMC_AVG_32, PMC_AVG_64, PMC_AVG_128
    * @param Start-upROM check: ROMCHE_ENABLED, ROMCHE_DISABLED
    * @param Common mode voltage measurement and check: CMVE_ENABLED, CMVE_DISABLED
    * @param sensor connection and RAM parity check: SCCD_ENABLED, SCCD_DISABLED
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setApplication(CFGAPP_VDCE analogVoltageCtrl = VDCE_ENABLED, CFGAPP_VDC analogVoltageCoarse = VDC_5V0, ADJREF_VDCA analogVoltageFine = VDCA_0P0, CFGCYC_PMC averaging = PMC_AVG_1, CFGCYC_ROMCHE romCheck = ROMCHE_ENABLED, CFGCYC_CMVE cmve = CMVE_DISABLED, CFGAPP_SCCD connectionCheck = SCCD_ENABLED);

    /*!
    * @brief set ZSC31050 clock settings
    * @param enable external clock: ECLKE_DISABLED, ECLKE_ENABLED
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setClock(CFGAPP_ECLKE clkEnable = ECLKE_DISABLED);

    /*!
    * @brief set ZSC31050 chip adjust
    * @param TC adjustment of internal bandgap voltage: [VREF_0 .. VREF_15]
    * @param Adjust bias current: [BCUR_0 ..BCUR_7]
    * @param Coarse oscillator frequency adjust: OSCF_1MHZ, OSCF_2MHZ, OSCF_4MHZ
    * @param Adjust oscillator frequency (F): OSCA_0F8, OSCA_0F85, OSCA_0F9, OSCA_0F95, OSCA_1F0, OSCA_1F05, OSCA_1F1, OSCA_1F15
    * @param clock divider for A/D converter: VFCCLKD_1, VFCCLKD_2
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setChipAdjust(ADJREF_VREF val = VREF_8, ADJREF_BCUR biasCurrent = BCUR_0, CFGAPP_OSCF oscFreqCoarse = OSCF_2MHZ, ADJREF_OSCA oscFreqFine = OSCA_1F0, CFGOUT_VFCCLKD clkDiv = VFCCLKD_1);

    /*!
    * @brief set ZSC31050 second I2C address
    * @param I2C address: [0x07 - 0x7F]
    * @param enable alternative I2C address: SIFID2E_ENABLED, SIFID2E_DISABLED
    * @return 0 - success
    * @return > 0 - error
    * @return 255 requested address not allowed
    */
    uint8_t setSecondI2CAddr(uint8_t addr = 0x79, CFGSIF_SIFID2E enable = SIFID2E_DISABLED);

    /*!
    * @brief set ZSC31050 Serial interface output selection
    * @param output of P to serial interface: SIFOUTP_ENABLED, SIFOUTP_DISABLED
    * @param output of T1 to serial interface: SIFOUTT1_ENABLED, SIFOUTT1_DISABLED
    * @param output of T2 to serial interface: SIFOUTT2_ENABLED, SIFOUTT2_DISABLED
    * @return 0 - success
    * @return > 0 - error
    */
    uint8_t setSIFOut(CFGSIF_SIFOUTP outP = SIFOUTP_ENABLED, CFGSIF_SIFOUTT1 outT1 = SIFOUTT1_ENABLED, CFGSIF_SIFOUTT2 outT2 = SIFOUTT2_DISABLED);

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

    /*!
    * @brief get amplified pressure output
    * @return pressure in ZSC units
    */
    int16_t getRawPressure(void);

    /*!
    * @brief get pressure output
    * @return pressure in ZSC units
    */
    uint16_t getCorrectedPressure(void);

    /*!
    * @brief get pressure in SI unit (Pascal)
    * @return pressure in Pascal
    */
    float getPressure(void);

    /*!
    * @brief get amplified T1 output
    * @return T1 in ZSC units
    */
    uint16_t getRawTemperature1(void);

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
    * @brief set serial interface of the ZSC31050
    * @param Interface: OWI, SPI1, SPI2, SPI3, SPI4, I2C
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return 1 - data too long to fit in transmit buffer
    * @return 2 - received NACK on transmit of address
    * @return 3 - received NACK on transmit of data
    * @return 4 - other error
    * @return 5 - tried to switch from normal mode to command or open mode (the device is stuck into normal mode once started)
    */
    uint8_t setInterface(Interface interface);

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
    * @brief set calibration output
    * @param Calibration Output: START_AD_P, START_AD_T1, START_AD_T2, START_AD_PAZ, START_AD_TAZ1, START_AD_TAZ2, START_AD_P_AZC, START_AD_T1_AZC,  TART_AD_T2_AZC, START_AD_CMV_AZC
    * @return (from Wire.endTransmission)
    * @return 0 - success
    * @return 1 - data too long to fit in transmit buffer
    * @return 2 - received NACK on transmit of address
    * @return 3 - received NACK on transmit of data
    * @return 4 - other error
    */
    uint8_t startCalibrationOutput(Calibration output);

  private:

    uint8_t _i2cAddr;

    Mode _mode;

    int16_t _P;

    int16_t _T1;

    int16_t _T2;

		int16_t rawP;

		int16_t correctedP;

		float correctedP_SI;

		int16_t rawT1;

    float _pressSlope = 1.2129015F;

    float _pressOffset = -1.552121F;

		uint8_t conversionTime = 23;

    uint8_t cmd(uint8_t cmd, uint16_t delay);
    uint8_t cmd(uint8_t cmd, uint16_t delay, uint16_t arg);

    template <typename cfgType> uint8_t cfg(uint8_t addr, uint16_t mask, cfgType val);

    uint16_t read16(void);
    uint64_t read48(void);
    void readOutput(void);


};
#endif