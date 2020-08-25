#include <M5Stack.h>
#include "background_process.h"

// #include <hidboot.h>     // USBおよびHIDBootを使うためにインクルード
// #include <BleKeyboard.h> // BleKeyboardを使うためにインクルード

// USB usb;
// HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hid_keyboard;
// BleKeyboard ble_keyboard;

void setup()
{
  // M5Stackを初期化
  // LCDとSerialのみ有効化
  M5.begin(true, false, true, false);

  // M5Stackをバッテリ―駆動する場合に必要
  M5.Power.begin();

  // バックグラウンド処理を初期化
  // M5.begin()の後に書く
  background_process.begin();
}

void loop()
{
  // update button state
  M5.update();

  if (M5.BtnA.wasPressed()) {
    keyboard_press_callback();
  }
}
