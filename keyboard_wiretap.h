#include <hidboot.h>     // USBおよびHIDBootを使うためにインクルード
#include <BleKeyboard.h> // BleKeyboardを使うためにインクルード
#include <Ticker.h>

class KeyboardWiretap {
 private:
  USB usb;
  HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hid_keyboard;
  BleKeyboard ble_keyboard;
  Ticker ticker;

 public:
  KeyboardWiretap();
  ~KeyboardWiretap();
  void begin();
  void set_keyboard_press_callback();
};
