#include <hidboot.h>     // USBおよびHIDBootを使うためにインクルード
#include <BleKeyboard.h> // BleKeyboardを使うためにインクルード

USB Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> HidKeyboard(&Usb);

BleKeyboard bleKeyboard;
