/*!
  \file kbd_d_matrix.cpp
  \brief AG-Panel Project digital matrix Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if 0 //defined(KBD_D_MATRIX)

#if !defined(KBD_ROWS) || !defined(KBD_COLS)
#error You should define KBD_ROWS and KBD_COLS for KBD_D_MATRIX!
#endif

#if ((KBD_COLS >= 1) && (!defined(KBD_PIN_C1))) \
  || ((KBD_COLS >= 2) && (!defined(KBD_PIN_C2))) \
  || ((KBD_COLS >= 3) && (!defined(KBD_PIN_C3))) \
  || ((KBD_COLS >= 4) && (!defined(KBD_PIN_C4)))
#error You should define proper amount of LCD_PIN_Cx for KBD_COLS of KBD_D_MATRIX!
#endif

#if ((KBD_ROWS >= 1) && (!defined(KBD_PIN_R1))) \
  || ((KBD_ROWS >= 2) && (!defined(KBD_PIN_R2))) \
  || ((KBD_ROWS >= 3) && (!defined(KBD_PIN_R3))) \
  || ((KBD_ROWS >= 4) && (!defined(KBD_PIN_R4)))
#error You should define proper amount of LCD_PIN_Rx for KBD_ROWS of KBD_D_MATRIX!
#endif

/*! \brief Initialization of keyboard
 */
void kbd_init() {
#if KBD_COLS >= 1
  pinMode(KBD_PIN_C1, OUTPUT);
#if KBD_COLS >= 2
  pinMode(KBD_PIN_C2, OUTPUT);
#if KBD_COLS >= 3
  pinMode(KBD_PIN_C3, OUTPUT);
#if KBD_COLS >= 4
  pinMode(KBD_PIN_C4, OUTPUT);
#endif
#endif
#endif
#endif
#if KBD_ROWS >= 1
  pinMode(KBD_PIN_R1, INPUT_PULLUP);
#if KBD_ROWS >= 2
  pinMode(KBD_PIN_R2, INPUT_PULLUP);
#if KBD_ROWS >= 3
  pinMode(KBD_PIN_R3, INPUT_PULLUP);
#if KBD_ROWS >= 4
  pinMode(KBD_PIN_R4, INPUT_PULLUP);
#endif
#endif
#endif
#endif
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
  static const uint8_t cols[] = {
#if KBD_COLS >= 1
    KBD_PIN_C1,
#if KBD_COLS >= 2
    KBD_PIN_C2,
#if KBD_COLS >= 3
    KBD_PIN_C3,
#if KBD_COLS >= 4
    KBD_PIN_C4,
#if KBD_COLS >= 5
#error Only 4 Columns are supported for now
#endif
#endif
#endif
#endif
#endif
  };
  static const uint8_t rows[] = {
#if KBD_ROWS >= 1
    KBD_PIN_R1,
#if KBD_ROWS >= 2
    KBD_PIN_R2,
#if KBD_ROWS >= 3
    KBD_PIN_R3,
#if KBD_ROWS >= 4
    KBD_PIN_R4,
#if KBD_ROWS >= 5
#error Only 4 Rows are supported for now
#endif
#endif
#endif
#endif
#endif
  };
  for(uint8_t c = 0; c < KBD_COLS; c++) {
    delayMicroseconds(5);
    for(uint8_t i = 0; i < KBD_COLS; i++) {
      digitalWrite(cols[i], i == c? LOW: HIGH);
    }
    delayMicroseconds(5);
    for(uint8_t r = 0; r < KBD_ROWS; r++) {
      uint16_t v = analogRead(rows[r]);
      if(v < 100) {
        for(uint8_t i = 0; i < KBD_COLS; i++) {
          digitalWrite(cols[i], HIGH);
        }
        return KBD_KEY(c, r);
      }
    }
  }
  for(uint8_t i = 0; i < KBD_COLS; i++) {
    digitalWrite(cols[i], HIGH);
  }
  return KBD_KEY_NONE;
}

#endif//KBD_D_MATRIX
