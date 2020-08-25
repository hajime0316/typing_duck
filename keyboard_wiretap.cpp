#include <M5Stack.h>
#include "keyboard_wiretap.h"

static const int TIMER_PERIOD = 10;

KeyboardWiretap keyboard_wiretap;

static void timer_callback();
void default_keyboard_press_callback();

void KeyboardWiretap::OnKeyDown(uint8_t mod, uint8_t key)
{
  Serial.println("Key Down!");
}

void KeyboardWiretap::OnKeyUp(uint8_t mod, uint8_t key)
{
  Serial.println("Key up!");
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
  if (usb_.Init() == -1)
    Serial.println("OSC did not start.");

  hid_keyboard_.SetReportParser(0, this);

  ticker_.attach_ms(TIMER_PERIOD, ::timer_callback);
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

void timer_callback()
{
  keyboard_wiretap.timer_callback();
}

void default_keyboard_press_callback()
{
  // デフォルトでは何もしない．
}
