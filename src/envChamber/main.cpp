#include <Arduino.h>
#include <Wire.h>
#include <TimerOne.h>

#include "board.h"

Board * board;

volatile uint8_t tick = false;
#define TOCK false;
void tikTok()
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
  board = new Board();
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(tikTok);
  for (;;) {
    if (tick) {
      board -> update();
      tick = TOCK;
    }
  }
  return 0;
}