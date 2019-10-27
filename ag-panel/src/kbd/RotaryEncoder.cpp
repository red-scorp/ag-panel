/*!
  \file RotaryEncoder.cpp
  \brief AG-Panel Project rotary encoder keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"
#include "RotaryEncoder.h"

bool RotaryEncoder::Init() {
  pinMode(m_D1Pin, INPUT_PULLUP);
  pinMode(m_D2Pin, INPUT_PULLUP);
  pinMode(m_ButtonPin, INPUT_PULLUP);
  return true;
}

void RotaryEncoder::Exit() {
}

uint8_t RotaryEncoder::GetKey() {

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

  uint8_t d1 = !digitalRead(m_D1Pin);
  uint8_t d2 = !digitalRead(m_D2Pin);
  uint8_t btn = digitalRead(m_ButtonPin);
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
          return KeyDefaultLeft;
        if(p_sum == 5) /* check direction (see table) */
          return KeyDefaultRight;
      }
      /* something went wrong? -> ignore! */
      sum = 0;
    }
  }

  if(btn == LOW)
    return KeyDefaultSelect;

  return KeyNone;
}
