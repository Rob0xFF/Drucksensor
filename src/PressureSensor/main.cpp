#include <Arduino.h>
#include <TimerOne.h>
#include <gui.h>

#define DTR_IRQ_PIN 2
#define FT6206_IRQ_PIN 3
#define USB_IRQ_PIN 71

GUI myGUI = GUI();

const uint8_t maxTouchDuration = 250;
volatile uint32_t touchDuration = 0;
volatile uint32_t touchStart = 0;
volatile uint16_t counter = 0;
volatile uint8_t touched = false;


#define IS_RELEASED false;
void tsTouched()
{
  if (counter == 0) {
    touchStart = millis();
    touched = true;
  } else {
    touchDuration = millis() - touchStart;
    if (touchDuration > maxTouchDuration) {
      counter = 0;
      return;
    }
  }
  counter ++;
}

volatile uint8_t tick = false;
#define TOCK false
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
  myGUI.boot();
  // interupt on touchscreen event
  pinMode(FT6206_IRQ_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(FT6206_IRQ_PIN), tsTouched, FALLING);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(tickTock);
  for (;;) {
    if (tick) {
      myGUI.update();
      tick = false;
    }
    if (touched) {
      myGUI.updateTouch();
      touched = IS_RELEASED;
    }
    if (Serial.available()) {
      if (myGUI.board.extSerial.parseSerialCommand()) {
        myGUI.board.extSerial.handleSerialCommand();
      }
    }
  }
  return 0;
}