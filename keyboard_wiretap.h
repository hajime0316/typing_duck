#ifndef KEYBOARD_WIRETAP_H_
#define KEYBOARD_WIRETAP_H_

#include <hidboot.h>     // USBおよびHIDBootを使うためにインクルード
#include <BleKeyboard.h> // BleKeyboardを使うためにインクルード

class KeyboardWiretap : KeyboardReportParser {
 private:
  USB usb_;
  HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hid_keyboard_;
  BleKeyboard ble_keyboard_;
  bool stop_sending_key_signal_flag;

 protected:
  void OnKeyDown(uint8_t mod, uint8_t key);
  void OnKeyUp(uint8_t mod, uint8_t key);
  void OnControlKeysChanged(uint8_t before, uint8_t after);

 public:
  KeyboardWiretap();
  ~KeyboardWiretap();
  void begin();
  void begin(void (*keyboard_press_callback_ptr)());
  void set_keyboard_press_callback(void (*keyboard_press_callback_ptr)());
  void task();
  uint8_t hid_usage_id_to_key_code(uint8_t hid_usage_id);
  void stop_sending_key_signal();
  void start_sending_key_signal();
};

extern KeyboardWiretap keyboard_wiretap;

#endif // KEYBOARD_WIRETAP_H_
