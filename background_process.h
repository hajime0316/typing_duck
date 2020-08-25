#ifndef BACKGROUND_PROCESS_HPP_
#define BACKGROUND_PROCESS_HPP_

#include <M5Stack.h>
#include <Ticker.h>

void keyboard_press_callback(); // TODO: この宣言をcppファイルに移動

class BackgroundProcess {
 private:
  Ticker ticker;

 public:
  BackgroundProcess();
  ~BackgroundProcess();
  void begin();
};

#endif // BACKGROUND_PROCESS_HPP_
