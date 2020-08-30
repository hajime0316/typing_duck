#include <M5Stack.h>
#include "background_process.h"
#include "keyboard_wiretap.h"
#include <algorithm>

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

  // 内部変数の初期化
  exp = 0;
  working_flag = false;
  working_time = 0;

  for (int i = 0; i < 5; i++) {
    shift_typing[i] = 0;
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
  // 現在時刻に更新
  present_time++;

  // 一定時間（5秒間）キーボード入力がないとステータスをWAITINGに変更する
  if (present_time - shift_typing[0] > 50) {
    typing_status = TypingStatus::WAITING;
  }

  // 作業時間をカウントする部分
  if (working_flag == true) {
    working_time++;
  }

  // ここから表示関連

  // 現在時刻を表示
  Serial.print("Present time: ");
  Serial.println(present_time);

  // 作業時間を表示
  Serial.print("Working time is");
  Serial.println(working_time);

  // 経験値を表示
  Serial.print("Exp. is");
  Serial.println(exp);

  // ステータスをSerial port へ表示する部分（デバッグ用）
  switch (typing_status) {
    case TypingStatus::WAITING:
      Serial.println("Status is WAITING");
      break;

    case TypingStatus::TYPING:
      Serial.println("Status is TYPING");
      break;

    case TypingStatus::PROMPTING_REST:
      Serial.println("Status is PROMPTING_REST");
      break;

    case TypingStatus::REJECTING_INPUT:
      Serial.println("Status is REJECTING_INPUT");
      break;

    default:
      break;
  }
}
// ここからkeyboard_press_callback関数
void BackgroundProcess::keyboard_press_callback()
{
  shift_typing[0] = present_time;
  std::sort(shift_typing, shift_typing + 5); //時刻が早い順に順に並び替え

  if (typing_status == TypingStatus::TYPING) {
    exp++;
  }

  int i = 0;

  for (i = 0; i < 4; i++) {
    if (shift_typing[i + 1] - shift_typing[i] > 10) {
      break;
    }
  }
  if (i == 4) {
    typing_status = TypingStatus::TYPING;
    working_flag = true;
  }

  Serial.println("Keyboard pressed!");
}
