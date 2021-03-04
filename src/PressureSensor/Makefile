PROJECT_DIR       = $(HOME)/MyArduinoProject/Drucksensor

ARDMK_DIR         = $(PROJECT_DIR)/Makefile

ARDUINO_DIR       = /Applications/Arduino.app/Contents/Java

ALTERNATE_CORE    = MegaCore

BOARD_SUB         = ATmega2560

BOARD_TAG         = 2560

VARIANT = 100-pin-arduino-mega

F_CPU = 16000000L

HEX_MAXIMUM_SIZE = 261120

ALTERNATE_VAR_PATH  = $(HOME)/Library/Arduino15/packages/MegaCore/hardware/avr/2.0.3

ALTERNATE_CORE_PATH = $(HOME)/Library/Arduino15/packages/MegaCore/hardware/avr/2.0.3

AVRDUDE_ARD_BAUDRATE = 115200

AVRDUDE_ARD_PROGRAMMER = arduino

ARDUINO_LIB_PATH = $(HOME)/Library/Arduino15/packages/MegaCore/hardware/avr/2.0.3/libraries

USER_LIB_PATH    :=  $(PROJECT_DIR)/lib

# Build user libs
ARDUINO_LIBS = Board Display TCA9548A ZSC31050 ZSC31050Serial GUI Screens Elements

# Build 3rd party libs
ARDUINO_LIBS += 3rdParty/FT6206 3rdParty/ILI9341TFT 3rdParty/TimerOne 3rdParty/HIH6130 3rdParty/INA226 3rdParty/MPRLS

# Build Libs included in Core
ARDUINO_LIBS += Wire SPI EEPROM

OPTIMIZATION_LEVEL = s

MONITOR_PORT      = /dev/cu.usbserial*

#MONITOR_PORT      = /dev/cu.usbmodem*

MONITOR_BAUDRATE  = 115200

AVR_TOOLS_DIR     = /usr/local

AVRDUDE           = /usr/local/bin/avrdude

AVRDUDE_OPTS      = -v -v

CFLAGS_STD        = -std=gnu11

CXXFLAGS_STD      = -std=gnu++14

CXXFLAGS         += -pedantic -Wall -Wextra 

LDFLAGS          += -fdiagnostics-color -Wl,-u,vfprintf -lprintf_flt -lm

CURRENT_DIR       = $(shell basename $(CURDIR))

OBJDIR            = $(PROJECT_DIR)/build/$(CURRENT_DIR)/$(BOARD_TAG)

include $(ARDMK_DIR)/Arduino.mk

