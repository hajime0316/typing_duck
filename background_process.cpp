#include "background_process.h"

static const int TIMER_PERIOD = 100;

void timer_callback();

BackgroundProcess::BackgroundProcess()
{
}

BackgroundProcess::~BackgroundProcess()
{
}

void BackgroundProcess::begin()
{
  ticker.attach_ms(TIMER_PERIOD, timer_callback);
}

void timer_callback()
{
  Serial.println("Timer Fire!");
}

void keyboard_press_callback()
{
  Serial.println("Keyboard pressed!");
}
