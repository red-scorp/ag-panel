/*!
  \file kbd.cpp
  \brief ALoS-Panel Project Keyboard code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "kbd.h"

/* Keyboard Configuration sanity check */
#if (!defined(KBD_NONE) && !defined(KBD_D_MATRIX) && !defined(KBD_A_JOYSTICK) && !defined(KBD_A_KEYPAD)) \
  || (defined(KBD_NONE) && defined(KBD_D_MATRIX)) \
  || (defined(KBD_NONE) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_NONE) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_A_KEYPAD))
#error You should define KBD_NONE, KBD_D_MATRIX, KBD_A_JOYSTICK or KBD_A_KEYPAD and only one of them!
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

#if defined(KBD_A_KEYPAD) && \
  (!defined(KBD_PIN_DATA))
#error You should define LCD_PIN_DATA for KBD_A_KEYPAD!
#endif

#if defined(KBD_A_KEYPAD) && \
  (!defined(KBD_DATA_NONE_MIN) || !defined(KBD_DATA_NONE_MAX) || (KBD_DATA_NONE_MIN > KBD_DATA_NONE_MAX) \
  || !defined(KBD_DATA_UP_MIN) || !defined(KBD_DATA_UP_MAX) || (KBD_DATA_UP_MIN > KBD_DATA_UP_MAX) \
  || !defined(KBD_DATA_DOWN_MIN) || !defined(KBD_DATA_DOWN_MAX) || (KBD_DATA_DOWN_MIN > KBD_DATA_DOWN_MAX) \
  || !defined(KBD_DATA_LEFT_MIN) || !defined(KBD_DATA_LEFT_MAX) || (KBD_DATA_LEFT_MIN > KBD_DATA_LEFT_MAX) \
  || !defined(KBD_DATA_RIGHT_MIN) || !defined(KBD_DATA_RIGHT_MAX) || (KBD_DATA_RIGHT_MIN > KBD_DATA_RIGHT_MAX) \
  || !defined(KBD_DATA_SELECT_MIN) || !defined(KBD_DATA_SELECT_MAX) || (KBD_DATA_SELECT_MIN > KBD_DATA_SELECT_MAX))
#error You should define proper ranges KBD_DATA_*_MIN and  KBD_DATA_*_MAX for KBD_A_KEYPAD!
#endif

/*! \brief Initialization of keyboard
 */
void kbd_init() {
#if defined(KBD_NONE)
  /* nothig to do here */
#elif defined(KBD_D_MATRIX)
  /* TODO: init pins */
#elif defined(KBD_A_JOYSTICK)
  pinMode(KBD_PIN_BTN, INPUT);
#elif defined(KBD_A_KEYPAD)
  /* No initialization for analog pins needed */
#endif
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
#if defined(KBD_NONE)
  /* No keys to read */
#elif defined(KBD_D_MATRIX)
  /* TODO: read keys */
#elif defined(KBD_A_JOYSTICK)
  int x = analogRead(KBD_PIN_X);
  int y = analogRead(KBD_PIN_Y);
  int btn = digitalRead(KBD_PIN_BTN);
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
#elif defined(KBD_A_KEYPAD)
  int data = analogRead(KBD_PIN_DATA);
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
#endif
  return KBD_KEY_NONE;
}
