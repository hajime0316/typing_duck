#include <M5Stack.h>
#include "keyboard_wiretap.h"

KeyboardWiretap keyboard_wiretap;

static const uint8_t HID_USAGE_ID_RETURN = 40;
static const uint8_t HID_USAGE_ID_BACKSPACE = 42;
static const uint8_t HID_USAGE_ID_DELETE = 76;
static const uint8_t HID_USAGE_ID_TAB = 43;
static const uint8_t HID_USAGE_ID_CAPS_LOCK = 57;
// static uint8_t HID_USAGE_ID_ESC = ;

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
  ble_keyboard_.press(hid_usage_id_to_key_code(key));
}

void KeyboardWiretap::OnKeyUp(uint8_t mod, uint8_t key)
{
  ble_keyboard_.release(hid_usage_id_to_key_code(key));
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

uint8_t KeyboardWiretap::hid_usage_id_to_key_code(uint8_t hid_usage_id)
{
  uint8_t key_code = OemToAscii(0, hid_usage_id);
  if (key_code != 0) return key_code;

  switch (hid_usage_id) {
    case HID_USAGE_ID_RETURN:
      return KEY_RETURN;
      break;
    case HID_USAGE_ID_BACKSPACE:
      return KEY_BACKSPACE;
      break;
    case HID_USAGE_ID_DELETE:
      return KEY_DELETE;
      break;
    case HID_USAGE_ID_TAB:
      return KEY_TAB;
      break;
    case HID_USAGE_ID_CAPS_LOCK:
      return KEY_CAPS_LOCK;
      break;
    default:
      break;
  }

  return 0;
}
