#include <Arduino.h>
#include <Wire.h>
#include <TimerOne.h>

#include "board.h"

Board * board;

volatile uint8_t tick = false;
#define TOCK false;
void tickTock()
{
  tick = true;
}

int atexit(void ( * /*func*/ )())
{
  return 0;
}

void initVariant() __attribute__((weak));
void initVariant() { }

int main(void)
{
  init();
  initVariant();
	Serial.begin(19200);
	Wire.begin();
	board = new Board();
	board -> begin();
  Timer1.initialize(500000);
  Timer1.attachInterrupt(tickTock);
  for (;;) {
    if (tick) {
      //board -> update();
      tick = TOCK;
    }
    if (Serial.available()) {
      if (board -> extSerial.parseSerialCommand()) {
        board -> extSerial.handleSerialCommand();
      }
    }
  }
  return 0;
}