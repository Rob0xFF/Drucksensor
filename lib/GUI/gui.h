#ifndef GUI_h
#define GUI_h

#include <new.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"
#include "glcdfont.c"
#include <board.h>
#include <screens.h>

class GUI
{
  public:
    /*!
      * @brief GUI class constructor.
      */
    GUI() {};
    /*!
      * @brief GUI boot sequence, boots hardware, shows main menu when ready.
      */
    void boot(void);
    /*!
      * @brief Here, we keep things going, calls mainboard update and screen updates, this is called each second by the main thread external timer interrupt.
      */
    void update(void);
    /*!
      * @brief Here, we keep things going, hich require high frequency updates, like LCD dimming and motor drive steps, this is called each millisecond by the main thread timer interrupt.
      */
    void fastUpdate(void);
    /*!
      * @brief Here, we assign touch events to their respective handlers, this is called by the main thread touch event interrupt once per touch event.
      */
    void updateTouch();
    /*!
      * @brief The GUI holds the instance of the motherboard hardware to operate with.
      */
    Board board = Board();

    /*!
      * @brief This is the screen header including temperature, humidity and status. This instance will never be destroyed.
      */
    ScreenHeader screenheader = ScreenHeader(board);

    /*!
      * @brief
      */
    MainScreen mainScreen = MainScreen(board);


  private:


    int16_t TouchX;
    int16_t TouchY;

    uint8_t currentScreen;

};

#endif