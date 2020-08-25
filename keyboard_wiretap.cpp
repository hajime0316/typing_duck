#include "keyboard_wiretap.h"

KeyboardWiretap keyboard_wiretap;

void timer_callback();
void default_keyboard_press_callback();

KeyboardWiretap::KeyboardWiretap() : hid_keyboard_(&usb_)
{
  keyboard_press_callback_ptr_ = default_keyboard_press_callback;
}

KeyboardWiretap::~KeyboardWiretap()
{
}

void KeyboardWiretap::begin()
{
  ticker_.attach_ms(100, ::timer_callback);
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
}

void timer_callback()
{
  keyboard_wiretap.timer_callback();
}

void default_keyboard_press_callback()
{
  // デフォルトでは何もしない．
}
