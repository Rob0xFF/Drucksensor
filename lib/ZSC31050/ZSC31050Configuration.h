#ifndef ZSC31050Configuration_h
#define ZSC31050Configuration_h

// ZSC31050 Configuration Flags

#define CFGCYC_PMC_MASK 0x0380
#define CFGCYC_ACOS2_MASK 0x0060
#define CFGCYC_ACOS1_MASK 0x0018
#define CFGCYC_CMVE_MASK 0x0004
#define CFGCYC_T2E_MASK 0x0002
#define CFGCYC_ROMCHE_MASK 0x0001

#define CFGSIF_SIFID2_MASK 0xFE00
//#define CFGSIF_OWIE_MASK 0x0100
#define CFGSIF_OWIWIND_MASK 0x0080
#define CFGSIF_SIFOUTT2_MASK 0x0040
#define CFGSIF_SIFOUTT1_MASK 0x0020
#define CFGSIF_SIFOUTP_MASK 0x0010
#define CFGSIF_SIFID2E_MASK 0x0008
//#define CFGSIF_SPICKE_MASK 0x0004
//#define CFGSIF_OWIE_MASK 0x0002
//#define CFGSIF_OWIE_MASK 0x0001

#define CFGAPP_BSP_MASK 0x8000
#define CFGAPP_ADRAIN3_MASK 0x3000
#define CFGAPP_IN3M_MASK 0x0C00
#define CFGAPP_SCCD_MASK 0x0200
#define CFGAPP_CSBE_MASK 0x0100
#define CFGAPP_XZCE_MASK 0x0080
#define CFGAPP_OSCF_MASK 0x0060
#define CFGAPP_ECLKE_MASK 0x0010
#define CFGAPP_ADREF_MASK 0x0008
#define CFGAPP_VDC_MASK 0x0006
#define CFGAPP_VDCE_MASK 0x0001

#define CFGAFE_RADC_MASK 0xE000
#define CFGAFE_OADC_MASK 0x0100
#define CFGAFE_ADRAPR_MASK 0x0C00
#define CFGAFE_XZC_POLARITY_MASK 0x0200
#define CFGAFE_XZC_MASK 0x01F0
#define CFGAFE_GAIN_MASK 0x000F

#define CFGTMP_GAINT2_MASK 0xC000
#define CFGTMP_GAINT1_MASK 0x3000
#define CFGTMP_PETS2_MASK 0x0800
#define CFGTMP_PETS1_MASK 0x0400
#define CFGTMP_ZCT2_MASK 0x0380
#define CFGTMP_ZCT1_MASK 0x0070
#define CFGTMP_TAM2_MASK 0x000C
#define CFGTMP_TAM1_MASK 0x0003

#define CFGOUT_PWMRES_MASK 0xC000
#define CFGOUT_PWMD_MASK 0x3000
#define CFGOUT_PWMPO2_MASK 0x0800
#define CFGOUT_PWMPO1_MASK 0x0400
#define CFGOUT_VFCCLKD_MASK 0x0100
#define CFGOUT_AWME_MASK 0x0080
#define CFGOUT_APO2_MASK 0x0040
#define CFGOUT_APO1_MASK 0x0020
#define CFGOUT_PMIO2_MASK 0x0010
#define CFGOUT_PMIO1_MASK 0x000C
#define CFGOUT_COS1_MASK 0x0003

#define ADJREF_CSB_MASK 0xE000
#define ADJREF_VDCA_MASK 0x1C00
#define ADJREF_OSCA_MASK 0x0380
#define ADJREF_BCUR_MASK 0x0070
#define ADJREF_VREF_MASK 0x000F


/*!
* @brief ZSC31050 Count of bridge measurements per cycle (averaging)
*/
enum CFGCYC_PMC {
  PMC_AVG_1 = 0x00 << 7,
  PMC_AVG_2 = 0x01 << 7,
  PMC_AVG_4 = 0x02 << 7,
  PMC_AVG_8 = 0x03 << 7,
  PMC_AVG_16 = 0x04 << 7,
  PMC_AVG_32 = 0x05 << 7,
  PMC_AVG_64 = 0x06 << 7,
  PMC_AVG_128 = 0x07 << 7
};

/*!
* @brief ZSC31050 Selection of output via IO1 pin (PWM), PWM at IO1 must be activated
*/
enum CFGCYC_ACOS2 {
  ACOS2_MEASURAND = 0b01 << 5,
  ACOS2_TEMPERATURE1 = 0b10 << 5,
  ACOS2_TEMPERATURE2 = 0b11 << 5
};

/*!
* @brief ZSC31050 Selection of output via OUT pin
*/
enum CFGCYC_ACOS1 {
  ACOS1_MEASURAND = 0b01 << 3,
  ACOS1_TEMPERATURE1 = 0b10 << 3,
  ACOS1_TEMPERATURE2 = 0b11 << 3
};

/*!
* @brief ZSC31050 Common mode voltage measurement and check
*/
enum CFGCYC_CMVE {
  CMVE_ENABLED = 0x01 << 2,
  CMVE_DISABLED = 0x00 << 2
};

/*!
* @brief ZSC31050 Temperature2 measurement
*/
enum CFGCYC_T2E {
  T2E_ENABLED = 0x01 << 1,
  T2E_DISABLED = 0x00 << 1
};

/*!
* @brief ZSC31050 Start-upROM check
*/
enum CFGCYC_ROMCHE {
  ROMCHE_ENABLED = 0x01,
  ROMCHE_DISABLED = 0x00
};

/*!
* @brief ZSC31050 start window for OWI interface
*/
enum CFGSIF_OWIWIND {
  OWIWIND_ENABLED = 0x00 << 7,
  OWIWIND_DISABLED = 0x01 << 7
};

/*!
* @brief ZSC31050 output of T2 to serial interface
*/
enum CFGSIF_SIFOUTT2 {
  SIFOUTT2_ENABLED = 0x01 << 6,
  SIFOUTT2_DISABLED = 0x00 << 6
};

/*!
* @brief ZSC31050 output of T1 to serial interface
*/
enum CFGSIF_SIFOUTT1 {
  SIFOUTT1_ENABLED = 0x01 << 5,
  SIFOUTT1_DISABLED = 0x00 << 5
};

/*!
* @brief ZSC31050 output of P to serial interface
*/
enum CFGSIF_SIFOUTP {
  SIFOUTP_ENABLED = 0x01 << 4,
  SIFOUTP_DISABLED = 0x00 << 4
};

/*!
* @brief ZSC31050 enable alternative I2C address
*/
enum CFGSIF_SIFID2E {
  SIFID2E_ENABLED = 0x01 << 3,
  SIFID2E_DISABLED = 0x00 << 3
};

/*!
* @brief ZSC31050 Bridge signal polarity
*/
enum CFGAPP_BSP {
  BSP_POSITIVE = 0x0 << 15,
  BSP_NEGATIVE = 0x1 << 15
};

/*!
* @brief ZSC31050 ADC range shift regarding signal from IN3 (TEMP2)
*/
enum CFGAPP_ADRAIN3 {
  ADRAIN3_15_16 = 0b00 << 12,
  ADRAIN3_7_8 = 0b01 << 12,
  ADRAIN3_3_4 = 0b10 << 12,
  ADRAIN3_1_2 = 0b11 << 12
};

/*!
* @brief ZSC31050 IN3 reference mode
*/
enum CFGAPP_IN3M {
  IN3M_BANDGAP = 0b00 << 10,
  IN3M_VDDA_2 = 0b01 << 10,
  IN3M_SUPPLY_VOLTAGE_CHECK = 0b10 << 10
};

/*!
* @brief ZSC31050 sensor connection and RAM parity check
*/
enum CFGAPP_SCCD {
  SCCD_ENABLED = 0b00 << 9,
  SCCD_DISABLED = 0b01 << 9
};

/*!
* @brief ZSC31050 bridge excitation mode
*/
enum CFGAPP_CSBE {
  CSBE_VOLTAGE = 0b00 << 8,
  CSBE_CURRENT = 0b01 << 8
};

/*!
* @brief ZSC31050 enable extended zero compensation
*/
enum CFGAPP_XZCE {
  XZCE_DISABLED = 0b00 << 7,
  XZCE_ENABLED = 0b01 << 7
};

/*!
* @brief ZSC31050 raw oscillator frequency adjust
*/
enum CFGAPP_OSCF {
  OSCF_1MHZ = 0b00 << 5,
  OSCF_2MHZ = 0b01 << 5,
  //OSCF_2MHZ = 0b10 << 5,
  OSCF_4MHZ = 0b11 << 5
};

/*!
* @brief ZSC31050 enable external clock
*/
enum CFGAPP_ECLKE {
  ECLKE_DISABLED = 0b0 << 4,
  ECLKE_ENABLED = 0b1 << 4
};

/*!
* @brief ZSC31050 A/D converter reference voltage selection
*/
enum CFGAPP_ADREF {
  ADREF_VBR = 0b00 << 3,
  ADREF_VDDA = 0b01 << 3
};

/*!
* @brief ZSC31050 VDDA controlled voltage
*/
enum CFGAPP_VDC {
  VDC_3V0 = 0b00 << 1,
  VDC_4V0 = 0b01 << 1,
  VDC_5V0 = 0b10 << 1,
  VDC_5V5 = 0b11 << 1
};

/*!
* @brief ZSC31050 analog voltage control (internal controller /w external transistor)
*/
enum CFGAPP_VDCE {
  VDCE_DISABLED = 0b0,
  VDCE_ENABLED = 0b1
};

/*!
* @brief ZSC31050 resolution of A/D conversion
*/
enum CFGAFE_RADC {
  RADC_9BIT = 0b000 << 13,
  RADC_10BIT = 0b001 << 13,
  RADC_11BIT = 0b010 << 13,
  RADC_12BIT = 0b011 << 13,
  RADC_13BIT = 0b100 << 13,
  RADC_14BIT = 0b101 << 13,
  RADC_15BIT = 0b110 << 13
};

/*!
* @brief ZSC31050 order of A/D conversion
*/
enum CFGAFE_OADC {
  OADC_1ST_ORDER = 0b00 << 12,
  OADC_2ND_ORDER = 0b01 << 12
};

/*!
* @brief ZSC31050 ADC range shift regarding measurand signal
*/
enum CFGAFE_ADRAPR {
  ADRAPR_15_16 = 0b00 << 10,
  ADRAPR_7_8 = 0b01 << 10,
  ADRAPR_3_4 = 0b10 << 10,
  ADRAPR_1_2 = 0b11 << 10
};

/*!
* @brief ZSC31050 eXtendedZeroCompensation value (offset compensation by analog front end XZCIN)
*/
enum CFGAFE_XZC_POLARITY {
  XZC_POLARITY_POSITIVE = 0b1 << 9,
  XZC_POLARITY_NEGATIVE = 0b0 << 9,
};

enum CFGAFE_XZC {
  XZC_0 = 0b00000 << 4,
  XZC_1 = 0b00001 << 4,
  XZC_2 = 0b00010 << 4,
  XZC_3 = 0b00011 << 4,
  XZC_4 = 0b00100 << 4,
  XZC_5 = 0b00101 << 4,
  XZC_6 = 0b00110 << 4,
  XZC_7 = 0b00111 << 4,
  XZC_8 = 0b01000 << 4,
  XZC_9 = 0b01001 << 4,
  XZC_10 = 0b01010 << 4,
  XZC_11 = 0b01011 << 4,
  XZC_12 = 0b01100 << 4,
  XZC_13 = 0b01101 << 4,
  XZC_14 = 0b01110 << 4,
  XZC_15 = 0b01111 << 4,
  XZC_16 = 0b10000 << 4,
  XZC_17 = 0b10001 << 4,
  XZC_18 = 0b10010 << 4,
  XZC_19 = 0b10011 << 4,
  XZC_20 = 0b10100 << 4,
  XZC_21 = 0b10101 << 4,
  XZC_22 = 0b10110 << 4,
  XZC_23 = 0b10111 << 4,
  XZC_24 = 0b11000 << 4,
  XZC_25 = 0b11001 << 4,
  XZC_26 = 0b11010 << 4,
  XZC_27 = 0b11011 << 4,
  XZC_28 = 0b11100 << 4,
  XZC_29 = 0b11101 << 4,
  XZC_30 = 0b11110 << 4,
  XZC_31 = 0b11111 << 4
};

/*!
* @brief ZSC31050 gain analog front end measurand measurement
*/
enum CFGAFE_GAIN {
  GAIN_420 = 0b0000,
  GAIN_280 = 0b0001,
  GAIN_210 = 0b0010,
  GAIN_140 = 0b0011,
  GAIN_105 = 0b0100,
  GAIN_70 = 0b0101,
  GAIN_52G5 = 0b0110,
  GAIN_35 = 0b0111,
  GAIN_26G25 = 0b1000,
  GAIN_14 = 0b1001,
  GAIN_9G3 = 0b1010,
  GAIN_7 = 0b1011,
  GAIN_2G8 = 0b1100,
};

/*!
* @brief ZSC31050 Gain analog front end temperature 2 meas.
*/
enum CFGTMP_GAINT2 {
  GAINT2_4 = 0b00 << 14,
  GAINT2_3 = 0b01 << 14,
  GAINT2_2 = 0b10 << 14,
  GAINT2_1 = 0b11 << 14
};

/*!
* @brief ZSC31050 Gain analog front end temperature 1 meas.
*/
enum CFGTMP_GAINT1 {
  GAINT1_4 = 0b00 << 12,
  GAINT1_3 = 0b01 << 12,
  GAINT1_2 = 0b10 << 12,
  GAINT1_1 = 0b11 << 12
};

/*!
* @brief ZSC31050 Polarity of external temperature sensor for temperature 2 measurement
*/
enum CFGTMP_PETS2 {
  PETS2_VSS = 0b0 << 11,
  PETS2_VDDA = 0b1 << 11
};

/*!
* @brief ZSC31050 Polarity of external temperature sensor for temperature 1 measurement
*/
enum CFGTMP_PETS1 {
  PETS1_VSS = 0b0 << 10,
  PETS1_VDDA = 0b1 << 10
};

/*!
* @brief ZSC31050 Temperature 2 (T2) zero-point adjust
*/
enum CFGTMP_ZCT2 {
  ZCT2_0 = 0b000 << 7,
  ZCT2_1 = 0b001 << 7,
  ZCT2_2 = 0b010 << 7,
  ZCT2_3 = 0b011 << 7,
  ZCT2_4 = 0b100 << 7,
  ZCT2_5 = 0b101 << 7,
  ZCT2_6 = 0b110 << 7,
  ZCT2_7 = 0b111 << 7
};

/*!
* @brief ZSC31050 Temperature 1 (T1) zero-point adjust
*/
enum CFGTMP_ZCT1 {
  ZCT1_0 = 0b000 << 4,
  ZCT1_1 = 0b001 << 4,
  ZCT1_2 = 0b010 << 4,
  ZCT1_3 = 0b011 << 4,
  ZCT1_4 = 0b100 << 4,
  ZCT1_5 = 0b101 << 4,
  ZCT1_6 = 0b110 << 4,
  ZCT1_7 = 0b111 << 4
};

/*!
* @brief ZSC31050 Temperature 2 (T2) acquisition mode
*/
enum CFGTMP_TAM2 {
  TAM2_INT_DIODE = 0b00 << 2,
  TAM2_EXT_DIODE = 0b01 << 2,
  TAM2_EXT_RES = 0b10 << 2,
  TAM2_EXT_VOLT = 0b11 << 2
};

/*!
* @brief ZSC31050 Temperature 1 (T1) acquisition mode
*/
enum CFGTMP_TAM1 {
  TAM1_INT_DIODE = 0b00,
  TAM1_EXT_DIODE = 0b01,
  TAM1_EXT_RES = 0b10
};

/*!
* @brief ZSC31050 PWM output resolution
*/
enum CFGOUT_PWMRES {
  PWMRES_9BIT = 0b00 << 14,
  PWMRES_10BIT = 0b01 << 14,
  PWMRES_11BIT = 0b10 << 14,
  PWMRES_12BIT = 0b11 << 14
};

/*!
* @brief ZSC31050 PWM CLK divider
*/
enum CFGOUT_PWMD {
  PWMD_1 = 0b00 << 12,
  PWMD_2 = 0b01 << 12,
  PWMD_4 = 0b10 << 12,
  PWMD_8 = 0b11 << 12
};

/*!
* @brief ZSC31050 PWM2 polarity
*/
enum CFGOUT_PWMPO2 {
  PWMPO2_HIGH = 0b0 << 11,
  PWMPO2_LOW = 0b1 << 11
};

/*!
* @brief ZSC31050 PWM1 polarity
*/
enum CFGOUT_PWMPO1 {
  PWMPO1_HIGH = 0b0 << 10,
  PWMPO1_LOW = 0b1 << 10
};

/*!
* @brief ZSC31050 clock divider for A/D converter
*/
enum CFGOUT_VFCCLKD {
  VFCCLKD_1 = 0b0 << 8,
  VFCCLKD_2 = 0b1 << 8
};

/*!
* @brief ZSC31050 alarm window mode
*/
enum CFGOUT_AWME {
  AWME_DISABLED = 0b00 << 7,
  AWME_ENABLED = 0b01 << 7
};

/*!
* @brief ZSC31050 alarm2 polarity
*/
enum CFGOUT_APO2 {
  APO2_LOW_ACTIVE = 0b0 << 6,
  APO2_HIGH_ACTIVE = 0b1 << 6
};

/*!
* @brief ZSC31050 alarm1 polarity
*/
enum CFGOUT_APO1 {
  APO1_LOW_ACTIVE = 0b0 << 5,
  APO1_HIGH_ACTIVE = 0b1 << 5
};

/*!
* @brief ZSC31050 output mode port IO2
*/
enum CFGOUT_PMIO2 {
  PMIO2_DISABLE = 0b0 << 4,
  PMIO2_ALARM2 = 0b1 << 4
};

/*!
* @brief ZSC31050 output mode port IO1
*/
enum CFGOUT_PMIO1 {
  PMIO1_DISABLE = 0b00 << 2,
  PMIO1_PWM1 = 0b10 << 2,
  PMIO1_ALARM1 = 0b11 << 2
};

/*!
* @brief ZSC31050 output mode port OUT
*/
enum CFGOUT_COS1 {
  COS1_VOLTAGE = 0b00,
  COS1_PWM2 = 0b10,
  COS1_CURRENT = 0b01,
  COS1_DISABLE = 0b11
};

/*!
* @brief ZSC31050 Adjust sensor bridge current factor (F)
*/
enum ADJREF_CSB {
  CSB_0F5 = 0b000 << 13,
  CSB_0F625 = 0b001 << 13,
  CSB_0F75 = 0b010 << 13,
  CSB_0F875 = 0b011 << 13,
  CSB_1F0 = 0b100 << 13,
  CSB_1F125 = 0b101 << 13,
  CSB_1F25 = 0b110 << 13,
  CSB_1F375 = 0b111 << 13
};

/*!
* @brief ZSC31050 Fine adjustment of controlled analog supply voltage (percent - P)
*/
enum ADJREF_VDCA {
  VDCA_M1P0 = 0b000 << 10,
  VDCA_M0P75 = 0b001 << 10,
  VDCA_M0P5 = 0b010 << 10,
  VDCA_M0P25 = 0b011 << 10,
  VDCA_0P0 = 0b100 << 10,
  VDCA_0P25 = 0b101 << 10,
  VDCA_0P5 = 0b110 << 10,
  VDCA_0P75 = 0b111 << 10
};

/*!
* @brief ZSC31050 Adjust oscillator frequency (F)
*/
enum ADJREF_OSCA {
  OSCA_0F8 = 0b000 << 7,
  OSCA_0F85 = 0b001 << 7,
  OSCA_0F9 = 0b010 << 7,
  OSCA_0F95 = 0b011 << 7,
  OSCA_1F0 = 0b100 << 7,
  OSCA_1F05 = 0b101 << 7,
  OSCA_1F1 = 0b110 << 7,
  OSCA_1F15 = 0b111 << 7
};

/*!
* @brief ZSC31050 Adjust bias current
*/
enum ADJREF_BCUR {
  BCUR_0 = 0b000 << 4,
  BCUR_1 = 0b001 << 4,
  BCUR_2 = 0b010 << 4,
  BCUR_3 = 0b011 << 4,
  BCUR_4 = 0b100 << 4,
  BCUR_5 = 0b101 << 4,
  BCUR_6 = 0b110 << 4,
  BCUR_7 = 0b111 << 4
};

/*!
* @brief ZSC31050 TC adjustment of internal bandgap voltage
*/
enum ADJREF_VREF {
  VREF_0 = 0b0000,
  VREF_1 = 0b0001,
  VREF_2 = 0b0010,
  VREF_3 = 0b0011,
  VREF_4 = 0b0100,
  VREF_5 = 0b0101,
  VREF_6 = 0b0110,
  VREF_7 = 0b0111,
  VREF_8 = 0b1000,
  VREF_9 = 0b1001,
  VREF_10 = 0b1010,
  VREF_11 = 0b1011,
  VREF_12 = 0b1100,
};

/*!
* @brief ZSC31050 working mode selector
*/
enum Mode {
  OPEN_MODE,
  NORMAL_MODE,
  COMMAND_MODE
};

/*!
* @brief ZSC31050 Interface
*/
enum Interface {
  OWI = 0x50,
	SPI1 = 0x51,
	SPI2 = 0x55,
	SPI3 = 0x59,
	SPI4 = 0x5D,
	I2C = 0x52
};

/*!
* @brief ZSC31050 Calibration Output
*/
enum Calibration {
  START_AD_P = 0xD0,
  START_AD_T1 = 0xD1,
  START_AD_T2 = 0xD2,
  START_AD_PAZ = 0xD4,
  START_AD_TAZ1 = 0xD5,
  START_AD_TAZ2 = 0xD6,
  START_AD_P_AZC = 0xD8,
  START_AD_T1_AZC = 0xD9,
  START_AD_T2_AZC = 0xDA,
  START_AD_CMV_AZC = 0xDB
};


#endif