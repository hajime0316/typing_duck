#include <M5Stack.h>
#include "background_process.h"
#include "keyboard_wiretap.h"
#include <algorithm>

// ここでBackgroundProcessクラスをインスタンス化する
// background_process.hをインクルードしたら，このインスタンスが使える
BackgroundProcess background_process;

static const int TIMER_PERIOD = 100;

static const int RESTING_TIME = 30;
static const int THRESHOLD_WORKING_STATE_TIME = 100;
static const int THRESHOLD_PROMPTING_REST_STATE_TIME = 100;

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

  waiting_state_time = 0;
  prompting_rest_state_time = 0;
  rejecting_input_time = 0;
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

  static TypingStatus following_typing_status = TypingStatus::REJECTING_INPUT;
  switch (typing_status) {
    case TypingStatus::WAITING:
      if (typing_status != following_typing_status) {
        init_waiting();
        following_typing_status = typing_status;
      }
      do_waiting();
      break;

    case TypingStatus::TYPING:
      if (typing_status != following_typing_status) {
        init_typing();
        following_typing_status = typing_status;
      }
      do_typing();
      break;

    case TypingStatus::PROMPTING_REST:
      if (typing_status != following_typing_status) {
        init_prompting_rest();
        following_typing_status = typing_status;
      }
      do_prompting_rest();
      break;

    case TypingStatus::REJECTING_INPUT:
      if (typing_status != following_typing_status) {
        init_rejecting_input();
        following_typing_status = typing_status;
      }
      do_rejecting_input();
      break;

    default:
      break;
  }

  // 一定時間（5秒間）キーボード入力がないとステータスをWAITINGに変更する
  if (present_time - shift_typing[0] > 50) {
    typing_status = TypingStatus::WAITING;
  }

  // TypingStatusがWAITINGの状態が一定時間続いたら，作業中フラグを折り，作業時間をリセット
  if (typing_status == TypingStatus::WAITING) {
    waiting_state_time++;
  }

  if (waiting_state_time > RESTING_TIME) {
    working_flag = false;
    working_time = 0;
  }

  // 作業時間をカウントする部分
  if (working_flag == true) {
    working_time++;
  }

  // 作業時間が一定時間以上になると休憩を促す
  if (working_time > THRESHOLD_WORKING_STATE_TIME) {
    typing_status = TypingStatus::PROMPTING_REST;
  }

  if (typing_status == TypingStatus::PROMPTING_REST) {
    prompting_rest_state_time++;
  }

  // 休憩を促しても入力が続くようならば，TypingStatusをREJECTING_INPUTに変更
  if (prompting_rest_state_time > THRESHOLD_PROMPTING_REST_STATE_TIME) {
    typing_status = TypingStatus::REJECTING_INPUT;
  }

  // 入力を拒否している時間をカウント
  if (typing_status == TypingStatus::REJECTING_INPUT) {
    rejecting_input_time++;
  }

  // 休憩時間分時間が経過すると，TypingStatusをWAITINGに変更
  if (rejecting_input_time > RESTING_TIME) {
    typing_status = TypingStatus::WAITING;
    rejecting_input_time = 0;
  }

  // ここから表示関連
  Serial.println("---------------");
  // 現在時刻を表示
  Serial.print("Present time: ");
  Serial.println(present_time);

  // 作業時間を表示
  Serial.print("Working time is ");
  Serial.println(working_time);

  // 経験値を表示
  Serial.print("Exp. is ");
  Serial.println(exp);

  // 作業中フラグを表示
  Serial.print("Working flag is ");
  Serial.println(working_flag);

  // TypingStatusがWAITINGになった時間を表示
  Serial.print("Waiting time is ");
  Serial.println(waiting_state_time);

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
  std::sort(shift_typing, shift_typing + 5); // 時刻が早い順に順に並び替え

  // TypingStatusがTYPINGであれば経験値を積算
  if (typing_status == TypingStatus::TYPING) {
    exp++;
  }

  // １秒以内の間隔で５入力あれば，TypingStatusをTYPINGに変更し，作業中フラグをTUREに
  int i = 0;

  for (i = 0; i < 4; i++) {
    if (shift_typing[i + 1] - shift_typing[i] > 10) {
      break;
    }
  }

  if (i == 4) {
    typing_status = TypingStatus::TYPING;
    working_flag = true;
    waiting_state_time = 0;
  }

  // 休憩の促しに関する部分
  if (typing_status == TypingStatus::PROMPTING_REST) {
    prompting_rest_state_time = 0;
    prompting_rest_type_num++;
  }

  //キーボードボタンが押されたことを示す
  Serial.println("Keyboard pressed!");
}

void BackgroundProcess::init_waiting()
{
}

void BackgroundProcess::do_waiting()
{
}

void BackgroundProcess::init_typing()
{
}

void BackgroundProcess::do_typing()
{
}

void BackgroundProcess::init_prompting_rest()
{
  prompting_rest_state_time = 0;
  prompting_rest_type_num = 0;
}

void BackgroundProcess::do_prompting_rest()
{
  prompting_rest_state_time++;
  if (prompting_rest_type_num > 5) {
    typing_status = TypingStatus::REJECTING_INPUT;
  }

  if (prompting_rest_state_time < RESTING_TIME) {
    typing_status = TypingStatus::WAITING;
  }
}

void BackgroundProcess::init_rejecting_input()
{
  rejecting_input_time = 0;
}

void BackgroundProcess::do_rejecting_input()
{
  rejecting_input_time++;
  if (rejecting_input_time > RESTING_TIME) {
    typing_status = TypingStatus::WAITING;
  }
}
