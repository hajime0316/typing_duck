#include <M5Stack.h>
#include "background_process.h"
#include "keyboard_wiretap.h"

// ここでBackgroundProcessクラスをインスタンス化する
// background_process.hをインクルードしたら，このインスタンスが使える
BackgroundProcess background_process;

static const int TIMER_PERIOD = 100;

static void global_timer_callback()
{
  background_process.timer_callback();
}

static void global_keyboard_press_callback()
{
  background_process.keyboard_press_callback();
}

BackgroundProcess::BackgroundProcess()
{
  present_time = 0;

  // ステータスの初期化
  typing_status = TypingStatus::WAITING;
  level_status = 0;
  evolution_status = 0;
  generation_status = 0;

  // 内部変数の初期化
  exp = 0;
  working_flag = false;
  for (size_t i = 0; i < TYPE_TIME_ARRAY_SIZE; i++)
  {
    type_time[i] = -1;
  }
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
  present_time++;

  Serial.println("Timer Fire!");
}

void BackgroundProcess::keyboard_press_callback()
{
  Serial.println("Keyboard pressed!");
}
