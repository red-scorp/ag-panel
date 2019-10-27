/*!
  \file kbd_rotary_encoder.cpp
  \brief AG-Panel Project Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if 0 //defined(KBD_ROTARY_ENCODER)

#if !defined(KBD_PIN_D1) || !defined(KBD_PIN_D2) \
  || !defined(KBD_PIN_BTN)
#error You should define KBD_PIN_D1, KBD_PIN_D2 and KBD_PIN_BTN for KBD_ROTARY_ENCODER!
#endif

/*! \brief Initialization of keyboard
 */
void kbd_init() {
  pinMode(KBD_PIN_D1, INPUT_PULLUP);
  pinMode(KBD_PIN_D2, INPUT_PULLUP);
  pinMode(KBD_PIN_BTN, INPUT_PULLUP);
  /* TODO: use attachInterrupt() and ISR if/when we have bad read timing! */
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
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
  return KBD_KEY_NONE;
}

#endif//KBD_ROTARY_ENCODER
