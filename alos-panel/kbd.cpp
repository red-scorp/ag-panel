/*!
  \file kbd.cpp
  \brief ALoS-Panel Project Keyboard code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "kbd.h"

/* Keyboard Configuration sanity check */
#if (!defined(KBD_NONE) && !defined(KBD_D_MATRIX) && !defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_NONE) && defined(KBD_D_MATRIX)) \
  || (defined(KBD_NONE) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_JOYSTICK))
#error You should define KBD_NONE, KBD_D_MATRIX or KBD_A_JOYSTICK and only one of them!
#endif

#if defined(KBD_D_MATRIX) && \
    (((KBD_COLS >= 1) && (!defined(KBD_PIN_C1))) \
  || ((KBD_COLS >= 2) && (!defined(KBD_PIN_C2))) \
  || ((KBD_COLS >= 3) && (!defined(KBD_PIN_C3))) \
  || ((KBD_COLS >= 4) && (!defined(KBD_PIN_C4))))
#error You should define proper amount of LCD_PIN_Cx for KBD_COLS of KBD_D_MATRIX!
#endif

#if defined(KBD_D_MATRIX) && \
    (((KBD_ROWS >= 1) && (!defined(KBD_PIN_R1))) \
  || ((KBD_ROWS >= 2) && (!defined(KBD_PIN_R2))) \
  || ((KBD_ROWS >= 3) && (!defined(KBD_PIN_R3))) \
  || ((KBD_ROWS >= 4) && (!defined(KBD_PIN_R4))))
#error You should define proper amount of LCD_PIN_Rx for KBD_ROWS of KBD_D_MATRIX!
#endif

#if defined(KBD_A_JOYSTICK) && \
  (!defined(KBD_PIN_X) || !defined(KBD_PIN_Y) \
  || !defined(KBD_PIN_BTN))
#error You should define KBD_PIN_X, KBD_PIN_Y and KBD_PIN_BTN for KBD_A_JOYSTICK!
#endif

void kbd_init() {
#if defined(KBD_NONE)
  /* nothig to do here */
#elif defined(KBD_D_MATRIX)
  /* TODO: init pins */
#elif defined(KBD_A_JOYSTICK)
  /* TODO: init pins */
#endif
}

uint8_t kbd_getkey() {
#if defined(KBD_NONE)
  return KBD_KEY_NONE;
#elif defined(KBD_D_MATRIX)
  return KBD_KEY_NONE; /* TODO: read keys */
#elif defined(KBD_A_JOYSTICK)
  return KBD_KEY_NONE; /* TODO: read keys */
#endif
}
