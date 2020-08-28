#include <M5Stack.h>
#include "keyboard_wiretap.h"

KeyboardWiretap keyboard_wiretap;

static const int TIMER_PERIOD = 10;
static void (*keyboard_press_callback_ptr_)();

static void global_timer_callback()
{
  keyboard_wiretap.timer_callback();
}

static void default_keyboard_press_callback()
{
  // デフォルトでは何もしない．
}

void KeyboardWiretap::OnKeyDown(uint8_t mod, uint8_t key)
{
  keyboard_press_callback_ptr_();
  ble_keyboard_.press(OemToAscii(0, key));
}

void KeyboardWiretap::OnKeyUp(uint8_t mod, uint8_t key)
{
  ble_keyboard_.release(OemToAscii(0, key));
}

void KeyboardWiretap::OnControlKeysChanged(uint8_t before, uint8_t after)
{
  if (before < after) {
    keyboard_press_callback_ptr_();
  }

  for (size_t i = 0; i < 8; i++) {
    if ((before >> i & 1) < (after >> i & 1)) {
      ble_keyboard_.press(i + KEY_LEFT_CTRL);
    }
    else if ((before >> i & 1) > (after >> i & 1)) {
      ble_keyboard_.release(i + KEY_LEFT_CTRL);
    }
  }
}

KeyboardWiretap::KeyboardWiretap() : hid_keyboard_(&usb_)
{
  keyboard_press_callback_ptr_ = default_keyboard_press_callback;
}

KeyboardWiretap::~KeyboardWiretap()
{
}

void KeyboardWiretap::begin()
{
  delay(200);

  if (usb_.Init() == -1)
    Serial.println("OSC did not start.");

  hid_keyboard_.SetReportParser(0, this);

  ble_keyboard_.begin();

  delay(1000);

  ticker_.attach_ms(TIMER_PERIOD, global_timer_callback);
}

void KeyboardWiretap::begin(void (*keyboard_press_callback_ptr)())
{
  set_keyboard_press_callback(keyboard_press_callback_ptr);
  begin();
}

void KeyboardWiretap::set_keyboard_press_callback(void (*keyboard_press_callback_ptr)())
{
  keyboard_press_callback_ptr_ = keyboard_press_callback_ptr;
}

void KeyboardWiretap::timer_callback()
{
  usb_.Task();
}

char KeyboardWiretap::hid_usage_id_to_key_code(char hid_usage_id)
{
  if (4 <= hid_usage_id && hid_usage_id <= 29) { // アルファベット
    return hid_usage_id - 4 + 'a';
  }
  else if (30 <= hid_usage_id && hid_usage_id <= 38) {
    return hid_usage_id - 30 + '1';
  }
  else if (hid_usage_id == 39) {
    return 48;
  }

  return 0;
}
