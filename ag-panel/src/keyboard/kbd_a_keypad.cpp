/*!
  \file kbd_a_keypad.cpp
  \brief AG-Panel Project analog keypad Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if 0 //defined(KBD_A_KEYPAD)

#if !defined(KBD_PIN_DATA)
#error You should define LCD_PIN_DATA for KBD_A_KEYPAD!
#endif

#if !defined(KBD_DATA_NONE_MIN) || !defined(KBD_DATA_NONE_MAX) || (KBD_DATA_NONE_MIN > KBD_DATA_NONE_MAX) \
  || !defined(KBD_DATA_UP_MIN) || !defined(KBD_DATA_UP_MAX) || (KBD_DATA_UP_MIN > KBD_DATA_UP_MAX) \
  || !defined(KBD_DATA_DOWN_MIN) || !defined(KBD_DATA_DOWN_MAX) || (KBD_DATA_DOWN_MIN > KBD_DATA_DOWN_MAX) \
  || !defined(KBD_DATA_LEFT_MIN) || !defined(KBD_DATA_LEFT_MAX) || (KBD_DATA_LEFT_MIN > KBD_DATA_LEFT_MAX) \
  || !defined(KBD_DATA_RIGHT_MIN) || !defined(KBD_DATA_RIGHT_MAX) || (KBD_DATA_RIGHT_MIN > KBD_DATA_RIGHT_MAX) \
  || !defined(KBD_DATA_SELECT_MIN) || !defined(KBD_DATA_SELECT_MAX) || (KBD_DATA_SELECT_MIN > KBD_DATA_SELECT_MAX)
#error You should define proper ranges KBD_DATA_*_MIN and KBD_DATA_*_MAX for KBD_A_KEYPAD!
#endif

/*! \brief Initialization of keyboard
 */
void kbd_init() {
  /* No initialization for analog pins needed */
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
  uint16_t data = analogRead(KBD_PIN_DATA);
  if(data >= KBD_DATA_UP_MIN && data < KBD_DATA_UP_MAX)
    return KBD_KEY_UP;
  if(data >= KBD_DATA_DOWN_MIN && data < KBD_DATA_DOWN_MAX)
    return KBD_KEY_DOWN;
  if(data >= KBD_DATA_LEFT_MIN && data < KBD_DATA_LEFT_MAX)
    return KBD_KEY_LEFT;
  if(data >= KBD_DATA_RIGHT_MIN && data < KBD_DATA_RIGHT_MAX)
    return KBD_KEY_RIGHT;
  if(data >= KBD_DATA_SELECT_MIN && data < KBD_DATA_SELECT_MAX)
    return KBD_KEY_SELECT;
  return KBD_KEY_NONE;
}

#endif//KBD_A_KEYPAD
