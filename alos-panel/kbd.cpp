/*!
  \file kbd.cpp
  \brief ALoS-Panel Project Keyboard code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "kbd.h"

/* Keyboard Configuration sanity check */
#if (!defined(KBD_NONE) && !defined(KBD_D_MATRIX) && !defined(KBD_A_JOYSTICK) \
  && !defined(KBD_A_KEYPAD) && !defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_NONE) && defined(KBD_D_MATRIX)) \
  || (defined(KBD_NONE) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_NONE) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_NONE) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_JOYSTICK)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_D_MATRIX) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_A_KEYPAD)) \
  || (defined(KBD_A_JOYSTICK) && defined(KBD_ROTARY_ENCODER)) \
  || (defined(KBD_A_KEYPAD) && defined(KBD_ROTARY_ENCODER))
#error You should define KBD_NONE, KBD_D_MATRIX, KBD_A_JOYSTICK, KBD_A_KEYPAD or KBD_ROTARY_ENCODER and only one of them!
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

#if defined(KBD_ROTARY_ENCODER) && \
  (!defined(KBD_PIN_D1) || !defined(KBD_PIN_D2) \
  || !defined(KBD_PIN_BTN))
#error You should define KBD_PIN_D1, KBD_PIN_D2 and KBD_PIN_BTN for KBD_ROTARY_ENCODER!
#endif

/*! \brief Initialization of keyboard
 */
void kbd_init() {
#if defined(KBD_NONE)
  /* nothig to do here */
#elif defined(KBD_D_MATRIX)
  /* TODO: init pins */
#elif defined(KBD_A_JOYSTICK)
  pinMode(KBD_PIN_BTN, INPUT_PULLUP);
#elif defined(KBD_A_KEYPAD)
  /* No initialization for analog pins needed */
#elif defined(KBD_ROTARY_ENCODER)
  pinMode(KBD_PIN_D1, INPUT_PULLUP);
  pinMode(KBD_PIN_D2, INPUT_PULLUP);
  pinMode(KBD_PIN_BTN, INPUT_PULLUP);
  /* TODO: use attachInterrupt() and ISR if/when we have bad read timing! */
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
#elif defined(KBD_ROTARY_ENCODER)
/*action| full left | full right| left&back | right&back|
  ------+-----------+-----------+-----------+-----------+
  !d1   | 0 1 1 0 0 | 0 0 1 1 0 | 0 1 1 1 0 | 0 0 1 0 0 |
  !d2   | 0 0 1 1 0 | 0 1 1 0 0 | 0 0 1 0 0 | 0 1 1 1 0 |
  d     | 0 1 3 2 0 | 0 2 3 1 0 | 0 1 3 1 0 | 0 2 3 2 0 |
  sum   | 0 1 4[6]0 | 0 2 5[6]0 | 0 1 4[5]0 | 0 2 5[7]0 |
  p_sum | ? 0 1[4]6 | ? 0 2[5]6 | ? 0 1 4 5 | ? 0 2 5 7 |
  ------+-----------+-----------+-----------+-----------+
  check |correct sum|correct sum| wrong sum!| wrong sum!|
  answer| p_sum = 4 | p_sum = 5 |  ignore!  |  ignore!  |*/
  uint8_t d1 = !digitalRead(KBD_PIN_D1);
  uint8_t d2 = !digitalRead(KBD_PIN_D2);
  uint8_t btn = digitalRead(KBD_PIN_BTN);
  uint8_t d = (d1 << 0) | (d2 << 1);
  static uint8_t p_d = 0;
  static uint8_t sum = 0;
  static uint8_t p_sum = 0;
  if(d != p_d) { /* do we have a state change? */
    p_d = d;
    if(d != 0) { /* are we still turning? */
      p_sum = sum;
      sum += d;
    } else { /* we have completed the turn */
      if(sum == 6) { /* do we have correct sum value? (see table) */
        sum = 0;
        if(p_sum == 4) /* check direction (see table) */
          return KBD_KEY_LEFT;
        if(p_sum == 5) /* check direction (see table) */
          return KBD_KEY_RIGHT;
      }
      /* something went wrong? -> ignore! */
      sum = 0;
    }
  }
  if(btn == LOW)
    return KBD_KEY_SELECT;
#endif
  return KBD_KEY_NONE;
}
