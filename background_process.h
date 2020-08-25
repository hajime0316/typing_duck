#ifndef BACKGROUND_PROCESS_H_
#define BACKGROUND_PROCESS_H_

#include <Ticker.h>

void global_keyboard_press_callback(); // TODO: この宣言をcppファイルに移動

class BackgroundProcess {
 private:
  Ticker ticker_;

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
