#ifndef BACKGROUND_PROCESS_H_
#define BACKGROUND_PROCESS_H_

#include <Ticker.h>
#include <time.h>

enum class TypingStatus {
  WAITING,        // 待機中
  TYPING,         // タイピング中
  PROMPTING_REST, // 休憩促し
  REJECTING_INPUT // 入力拒否
};

class BackgroundProcess {
 private:
  Ticker ticker_;
  time_t present_time; // 電源を入れてから現在までの時刻[100ms]

  // ステータス
  TypingStatus typing_status; // 待機中やタイピング中などの状態がある

  // 内部変数
  int exp;          // 経験値
  int working_flag; //作業中フラグ．作業が続いている場合はtrue

  int shift_typing[5]; // キーボード入力を行った時刻を記録．

  int working_time; // 作業時間の合計を記録

  int waiting_state_time; // 待機中の時間をカウント

 public:
  BackgroundProcess();
  ~BackgroundProcess();
  void begin();
  void timer_callback();
  void keyboard_press_callback();
  // ゲッター
  TypingStatus get_typing_status() const { return typing_status; };
  int get_exp() const { return exp; };
  // 経験値関係
  void reset_exp() { exp = 0; };
};

// cppファイル内でBackgroundProcessクラスをインスタンス化する
// background_process.hをインクルードしたら，このインスタンスが使える
extern BackgroundProcess background_process;

#endif // BACKGROUND_PROCESS_H_
