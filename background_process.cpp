#include <M5Stack.h>
#include "background_process.h"
#include "keyboard_wiretap.h"

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
  keyboard_wiretap.begin(keyboard_press_callback);
  ticker_.attach_ms(TIMER_PERIOD, timer_callback);
}

void timer_callback()
{
  Serial.println("Timer Fire!");
}

void keyboard_press_callback()
{
  Serial.println("Keyboard pressed!");
}

// ここでBackgroundProcessクラスをインスタンス化する
// background_process.hをインクルードしたら，このインスタンスが使える
BackgroundProcess background_process;
