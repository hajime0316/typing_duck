#ifndef BACKGROUND_PROCESS_H_
#define BACKGROUND_PROCESS_H_

#include <Ticker.h>

enum class TypingStatus {
  WAITING,         // 待機中
  TYPING,         // タイピング中
  PROMPTING_REST, // 休憩促し
  REJECTING_INPUT // 入力拒否
};

class BackgroundProcess {
 private:
  Ticker ticker_;
  time_t present_time; // 電源を入れてから現在までの時刻[100ms]

  // ステータス
  TypingStatus typing_status;
  int level_status;
  int generation_status;
  int evolution_status;

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
