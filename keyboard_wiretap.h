#ifndef KEYBOARD_WIRETAP_H_
#define KEYBOARD_WIRETAP_H_

#include <hidboot.h>     // USBおよびHIDBootを使うためにインクルード
#include <BleKeyboard.h> // BleKeyboardを使うためにインクルード
#include <Ticker.h>

class KeyboardWiretap : KeyboardReportParser {
 private:
  USB usb_;
  HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hid_keyboard_;
  BleKeyboard ble_keyboard_;
  Ticker ticker_;
  void (*keyboard_press_callback_ptr_)();

 protected:
  void OnKeyDown(uint8_t mod, uint8_t key);
  void OnKeyUp(uint8_t mod, uint8_t key);

 public:
  KeyboardWiretap();
  ~KeyboardWiretap();
  void begin();
  void begin(void (*keyboard_press_callback_ptr)());
  void set_keyboard_press_callback(void (*keyboard_press_callback_ptr)());
  void timer_callback();
};

#endif // KEYBOARD_WIRETAP_H_
