#ifndef BACKGROUND_PROCESS_H_
#define BACKGROUND_PROCESS_H_

#include <Ticker.h>
#include <time.h>

const int SHIFT_TYPING_SIZE = 5;

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

  int shift_typing[SHIFT_TYPING_SIZE]; // キーボード入力を行った時刻を記録．

  int working_time; // 作業時間の合計を記録

  int waiting_time; // 待機中の時間をカウント

  int prompting_rest_state_time; // 休憩を促している時間をカウント
  int prompting_rest_typing_num;   // 休憩を促している時のタイプ数をカウント

  int rejecting_input_time; //入力を拒否している時間をカウント

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

 protected:
  void init_waiting();
  void do_waiting();
  void init_typing();
  void do_typing();
  void init_prompting_rest();
  void do_prompting_rest();
  void init_rejecting_input();
  void do_rejecting_input();
};

// cppファイル内でBackgroundProcessクラスをインスタンス化する
// background_process.hをインクルードしたら，このインスタンスが使える
extern BackgroundProcess background_process;

#endif // BACKGROUND_PROCESS_H_
