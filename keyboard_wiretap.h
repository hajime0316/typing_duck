#include <hidboot.h>     // USBおよびHIDBootを使うためにインクルード
#include <BleKeyboard.h> // BleKeyboardを使うためにインクルード

class KeyboardWiretap {
 private:
  USB usb;
  HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hid_keyboard;
  BleKeyboard ble_keyboard;

 public:
  KeyboardWiretap();
  ~KeyboardWiretap();
};
