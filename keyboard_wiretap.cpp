#include "keyboard_wiretap.h"

void default_keyboard_press_callback()
{
  // デフォルトでは何もしない．
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