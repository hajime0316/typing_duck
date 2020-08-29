#ifndef BACKGROUND_PROCESS_H_
#define BACKGROUND_PROCESS_H_

#include <Ticker.h>

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
  int level_status;           // レベルを表す
  int evolution_status;       // 進化の段階を表す．ダックは0で進化するごとに1増える
  int generation_status;      // 世代を表す

 public:
  BackgroundProcess();
  ~BackgroundProcess();
  void begin();
  void timer_callback();
  void keyboard_press_callback();
};

// cppファイル内でBackgroundProcessクラスをインスタンス化する
// background_process.hをインクルードしたら，このインスタンスが使える
extern BackgroundProcess background_process;

#endif // BACKGROUND_PROCESS_H_
