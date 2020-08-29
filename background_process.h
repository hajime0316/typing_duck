#ifndef BACKGROUND_PROCESS_H_
#define BACKGROUND_PROCESS_H_

#include <Ticker.h>

class BackgroundProcess {
 private:
  Ticker ticker_;
  time_t present_time; // 電源を入れてから現在までの時刻[100ms]

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
