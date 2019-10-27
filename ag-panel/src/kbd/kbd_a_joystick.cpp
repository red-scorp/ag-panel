/*!
  \file kbd_a_joystick.cpp
  \brief AG-Panel Project analog joystick Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if 0 //defined(KBD_A_JOYSTICK)

#if !defined(KBD_PIN_X) || !defined(KBD_PIN_Y) \
  || !defined(KBD_PIN_BTN)
#error You should define KBD_PIN_X, KBD_PIN_Y and KBD_PIN_BTN for KBD_A_JOYSTICK!
#endif

/*! \brief Initialization of keyboard
 */
void kbd_init() {
  pinMode(KBD_PIN_BTN, INPUT_PULLUP);
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
  uint16_t x = analogRead(KBD_PIN_X);
  uint16_t y = analogRead(KBD_PIN_Y);
  uint8_t btn = digitalRead(KBD_PIN_BTN);
  if(btn == LOW)
    return KBD_KEY_SELECT;
  if(x < (KBD_X_CENTER - KBD_THRESHOLD))
    return KBD_KEY_LEFT;
  if(x > (KBD_X_CENTER + KBD_THRESHOLD))
    return KBD_KEY_RIGHT;
  if(y < (KBD_Y_CENTER - KBD_THRESHOLD))
    return KBD_KEY_DOWN;
  if(y > (KBD_Y_CENTER + KBD_THRESHOLD))
    return KBD_KEY_UP;
  return KBD_KEY_NONE;
}

#endif//KBD_A_JOYSTICK
