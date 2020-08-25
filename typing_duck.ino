#include <hidboot.h>     // USBおよびHIDBootを使うためにインクルード
#include <BleKeyboard.h> // BleKeyboardを使うためにインクルード

USB usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hid_keyboard;
BleKeyboard ble_keyboard;

void setup()
{
}

void loop()
{
}
