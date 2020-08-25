#ifndef BACKGROUND_PROCESS_HPP_
#define BACKGROUND_PROCESS_HPP_

class BackgroundProcess {
 private:

 public:
  BackgroundProcess();
  ~BackgroundProcess();
  void begin();
  void timer_callback();
  void keyboard_press_callback();
};

#endif // BACKGROUND_PROCESS_HPP_
