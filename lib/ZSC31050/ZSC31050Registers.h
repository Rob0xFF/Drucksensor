#ifndef ZSC31050Registers_h
#define ZSC31050Registers_h


// ZSC31050 Command Registers

#define START_CYC_EEP 0x01, 5350
#define START_CYC_RAM 0x02, 65535
#define CFG_SIF_TO_I2C 0x52, 50
#define CFG_SIF_TO_OWI 0x50, 50
#define SET_DAC 0x60, 100
#define START_OM 0x70, 50
#define START_NOM 0x71, 50
#define START_CM 0x72, 50
#define ROM_VERSION 0xCF, 50
#define COPY_RAM2EEP 0xC3, 0 // delay must be handled by function here, otherwise delayMicroseconds will overflow

// ZSC31050 RAM Registers

#define C0_OFFSET 0x00
#define C1_GAIN 0x01
#define C2_NONLIN_2ND 0x02
#define C3_NONLIN_3RD 0x03
#define C4_TEMP_OFFS_1ST 0x04
#define C5_TEMP_OFFS_2ND 0x05
#define C4_TEMP_GAIN_1ST 0x06
#define C4_TEMP_GAIN_2ND 0x07

#define OUT_LOW_LIM 0x08
#define OUT_HIGH_LIM 0x09

#define TEMP1_OFFS_1ST 0x0A
#define TEMP1_GAIN 0x0B
#define TEMP1_NONLIN_2ND 0x0C
#define TEMP2_OFFS_1ST 0x0D
#define TEMP2_GAIN 0x0E
#define TEMP2_NONLIN_2ND 0x0F

#define ALM1_THD_PWM_LOW_LIM 0x10
#define ALM1_HYS_PWM_UP_LIM 0x11
#define ALM1_DELAY 0x12
#define ALM2_THD_PWM_LOW_LIM 0x13
#define ALM2_HYS_PWM_UP_LIM 0x14
#define ALM2_DELAY 0x15

#define CFGCYC 0x16
#define CFGSIF 0x17
#define CFGAPP 0x18
#define CFGAFE 0x19
#define CFGTMP 0x1A
#define CFGOUT 0x1B
#define ADJREF 0x1C
#define SIG 0x1D

/*!
* @brief Register
*/
enum Register {
  USR_VAL1 = 0x1E,
  USR_VAL2 = 0x1F
};

#define READ_RAM_OFFS 0x10
#define READ_EEPROM_OFFS 0x30
#define WRITE_RAM_OFFS 0x80
#define WRITE_EEPROM_OFFS 0xA0

#define READ_RAM_DELAY 50
#define READ_EEPROM_DELAY 50
#define WRITE_RAM_DELAY 50
#define WRITE_EEPROM_DELAY 12500

#endif