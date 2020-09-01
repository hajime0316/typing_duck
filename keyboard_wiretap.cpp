#include <M5Stack.h>
#include "keyboard_wiretap.h"

KeyboardWiretap keyboard_wiretap;

static const uint8_t HID_USAGE_ID_RETURN = 40;
static const uint8_t HID_USAGE_ID_BACKSPACE = 42;
static const uint8_t HID_USAGE_ID_DELETE = 76;
static const uint8_t HID_USAGE_ID_TAB = 43;
static const uint8_t HID_USAGE_ID_CAPS_LOCK = 57;
static const uint8_t HID_USAGE_ID_ESC = 41;
static const uint8_t HID_USAGE_ID_INSERT = 73;
static const uint8_t HID_USAGE_ID_HONE = 74;
static const uint8_t HID_USAGE_ID_PAGE_UP = 75;
static const uint8_t HID_USAGE_ID_END = 77;
static const uint8_t HID_USAGE_ID_PAGE_DOWN = 78;

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

  if (stop_sending_key_signal_flag) return;

  ble_keyboard_.press(hid_usage_id_to_key_code(key));
}

void KeyboardWiretap::OnKeyUp(uint8_t mod, uint8_t key)
{
  if (stop_sending_key_signal_flag) return;

  ble_keyboard_.release(hid_usage_id_to_key_code(key));
}

void KeyboardWiretap::OnControlKeysChanged(uint8_t before, uint8_t after)
{
  if (before < after) {
    keyboard_press_callback_ptr_();
  }

  if (stop_sending_key_signal_flag) return;

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
  stop_sending_key_signal_flag = false;
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
    case HID_USAGE_ID_ESC:
      return KEY_ESC;
      break;
    case HID_USAGE_ID_INSERT:
      return KEY_INSERT;
      break;
    case HID_USAGE_ID_HONE:
      return KEY_HOME;
      break;
    case HID_USAGE_ID_PAGE_UP:
      return KEY_PAGE_UP;
      break;
    case HID_USAGE_ID_END:
      return KEY_END;
      break;
    case HID_USAGE_ID_PAGE_DOWN:
      return KEY_PAGE_DOWN;
      break;
    default:
      break;
  }

  // 矢印
  if (79 <= hid_usage_id && hid_usage_id <= 82) {
    return hid_usage_id - 79 + KEY_RIGHT_ARROW;
  }

  uint8_t key_code = OemToAscii(0, hid_usage_id);
  if (key_code != 0) return key_code;

  return 0;
}

void KeyboardWiretap::stop_sending_key_signal()
{
  ble_keyboard_.releaseAll();
  stop_sending_key_signal_flag = true;
}

void KeyboardWiretap::start_sending_key_signal()
{
  stop_sending_key_signal_flag = false;
}
