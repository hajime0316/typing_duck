#ifndef BACKGROUND_PROCESS_HPP_
#define BACKGROUND_PROCESS_HPP_

#include <hidboot.h>     // USBおよびHIDBootを使うためにインクルード
#include <BleKeyboard.h> // BleKeyboardを使うためにインクルード

class BackgroundProcess {
 private:
  USB usb;
  HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hid_keyboard;
  BleKeyboard ble_keyboard;

 public:
  BackgroundProcess();
  ~BackgroundProcess();
  void begin();
  void timer_callback();
  void keyboard_press_callback();
};

#endif // BACKGROUND_PROCESS_HPP_
