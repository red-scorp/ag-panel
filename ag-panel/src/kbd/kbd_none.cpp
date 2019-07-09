/*!
  \file kbd_none.cpp
  \brief AG-Panel Project none Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if defined(KBD_NONE)

/*! \brief Initialization of keyboard
 */
void kbd_init() {
  /* nothig to do here */
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
  /* No keys to read */
  return KBD_KEY_NONE;
}

#endif//KBD_NONE
