#include <M5Stack.h>
#include "background_process.h"
#include "keyboard_wiretap.h"

// ここでBackgroundProcessクラスをインスタンス化する
// background_process.hをインクルードしたら，このインスタンスが使える
BackgroundProcess background_process;

static const int TIMER_PERIOD = 50;

static void global_timer_callback();

BackgroundProcess::BackgroundProcess()
{
}

BackgroundProcess::~BackgroundProcess()
{
}

void BackgroundProcess::begin()
{
  keyboard_wiretap.begin(global_keyboard_press_callback);
  ticker_.attach_ms(TIMER_PERIOD, global_timer_callback);
}

void BackgroundProcess::timer_callback()
{
  Serial.println("Timer Fire!");
}

void BackgroundProcess::keyboard_press_callback()
{
  Serial.println("Keyboard pressed!");
}

void global_timer_callback()
{
  background_process.timer_callback();
}

void global_keyboard_press_callback()
{
  background_process.keyboard_press_callback();
}
