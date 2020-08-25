#ifndef BACKGROUND_PROCESS_HPP_
#define BACKGROUND_PROCESS_HPP_

#include <Ticker.h>

class BackgroundProcess {
 private:
  Ticker ticker;

 public:
  BackgroundProcess();
  ~BackgroundProcess();
  void begin();
  void timer_callback();
  void keyboard_press_callback();
};

#endif // BACKGROUND_PROCESS_HPP_
