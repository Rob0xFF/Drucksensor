#ifndef BOARD_h
#define BOARD_h

#include "Arduino.h"
#include "Wire.h"
#include "ZSC31050.h"
#include "ZSC31050Serial.h"

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <display.h>
#include <new.h>
#include <Adafruit_FT6206.h>
#include <TCA9548A.h>
#include <HIH61XX.h>
#include <INA226.h>
#include <EEPROM.h>
#include <Adafruit_MPRLS.h>
#include <Adafruit_MCP4725.h>
#include <envChamber.h>

const uint8_t I2C_TCA = 0x70;
const uint8_t I2C_INA226 = 0x40;
const uint8_t I2C_HIH6130 = 0x27;
const uint8_t I2C_ZSC31050 = 0x78;
const uint8_t I2C_FT6206 = 0x38;
const uint8_t I2C_MCP4725 = 0x60;
const uint8_t I2C_MPRLS = 0x18;

const uint8_t USB_PIN = 71;

const uint8_t TCA = 0;
const uint8_t INA226_INT = 1;
const uint8_t HIH6130_INT = 2;
const uint8_t INA226_EXT = 3;
const uint8_t HIH6130_EXT = 4;
const uint8_t ZSC31050_INT = 5;
const uint8_t ZSC31050_EXT = 6;
const uint8_t FT6206 = 7;
const uint8_t MCP4725 = 8;
const uint8_t MPRLS = 9;
const uint8_t USB_CONN = 10;
const uint8_t SOFT_CONN = 11;

const uint8_t UNKNOWN = 3;
const uint8_t DISABLED = 2;
const uint8_t EXT = 1;
const uint8_t INT = 0;

const uint8_t TO_EEPROM = 1;
const uint8_t TO_RAM = 0;

class Board
{
  public:

    Board()
    {
    };

    void begin(void);

    void update(void);

    void checkEXT(void);

    /*!
     * @brief manage availability of hardware
     */
    inline void available(uint8_t bit)
    {
      _isAvailable |= 1UL << bit;
    };
    inline void unAvailable(uint8_t bit)
    {
      _isAvailable &= ~(1UL << bit);
    };
    inline uint8_t isAvailable(uint8_t bit)
    {
      if (_isAvailable & 1UL << bit) {
        return 1;
      } else {
        return 0;
      }
    };

    void saveScreenshot(void);

    ZSC31050Serial extSerial = ZSC31050Serial(Serial);

    EnvChamber envChamber = EnvChamber(Serial3, '6');

    Adafruit_FT6206 touchScreen = Adafruit_FT6206();

    Display TFT = Display();

    float temperatureINT = 0.0;

    float humidityINT = 0.0;

    float temperatureEXT = 0.0;

    float humidityEXT = 0.0;

    float senTemperature = 0.0;

    float senHumidity = 0.0;

    float bridgeVoltageINT = 0.0;

    float voltageINT = 0.0;

    float bridgeVoltageEXT = 0.0;

    float voltageEXT = 0.0;

    float senBridgeVoltage = 0.0;

    float senVoltage = 0.0;

    uint16_t chipIDINT = 0;

    uint16_t chipIDEXT = 0;

    uint16_t senChipID = 0;

    float slopeINT = 0;

    float offsetINT = 0;

    float slopeEXT = 0;

    float offsetEXT = 0;

    float senSlope = 0;

    float senOffset = 0;

    int16_t rawP;

    int16_t P;

    float P_SI;

    int16_t T1;

    int16_t T2;

    float mprPres = 0.0;

    float mprPresZero = 0.0;

    float mprPresRelative = 0.0;

    volatile uint8_t sensorStatus = UNKNOWN;

    Adafruit_MCP4725 dac;

    Adafruit_MPRLS mpr = Adafruit_MPRLS(-1, -1);


  private:

    TCA9548A multiplexer = TCA9548A(I2C_TCA);

    uint8_t memBufferZscINT[sizeof(ZSC31050)];
    ZSC31050 * zscINT;

    uint8_t memBufferZscEXT[sizeof(ZSC31050)];
    ZSC31050 * zscEXT;

    INA226 voltageSensorINT = INA226();

    uint8_t memBufferVoltageSensorEXT[sizeof(INA226)];
    INA226 * voltageSensorEXT;

    HIH61XX HIHINT = HIH61XX(I2C_HIH6130, 255);

    uint8_t memBufferHIHEXT[sizeof(HIH61XX)];
    HIH61XX * HIHEXT;

    volatile uint16_t _isAvailable = 0x0;

};
#endif