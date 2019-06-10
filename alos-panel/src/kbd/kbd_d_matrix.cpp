/*!
  \file kbd_d_matrix.cpp
  \brief ALoS-Panel Project digital matrix Keyboard code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if defined(KBD_D_MATRIX)

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

#if !defined(KBD_ROWS) || !defined(KBD_COLS)
#error You should define KBD_ROWS and KBD_COLS for KBD_A_MATRIX!
#endif

#if !defined(KBD_PIN_DATA)
#error You should define LCD_PIN_DATA for KBD_A_MATRIX!
#endif

#if !defined(KBD_DATA_TOLERANCE) || !defined(KBD_DATA_ARRAY)
#error You should define proper KBD_DATA_TOLERANCE and KBD_DATA_ARRAY for KBD_A_MATRIX!
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
  uint8_t cols[] = {
#if KBD_COLS >= 1
    KBD_PIN_C1,
#if KBD_COLS >= 2
    KBD_PIN_C2,
#if KBD_COLS >= 3
    KBD_PIN_C3,
#if KBD_COLS >= 4
    KBD_PIN_C4,
#endif
#endif
#endif
#endif
  };
  uint8_t rows[] = {
#if KBD_ROWS >= 1
    KBD_PIN_R1,
#if KBD_ROWS >= 2
    KBD_PIN_R2,
#if KBD_ROWS >= 3
    KBD_PIN_R3,
#if KBD_ROWS >= 4
    KBD_PIN_R4,
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
        uint8_t x = 0;
        x |= c << 4;
        x |= 1 << r;
        for(uint8_t i = 0; i < KBD_COLS; i++) {
          digitalWrite(cols[i], HIGH);
        }
        return x;
      }
    }
  }
  for(uint8_t i = 0; i < KBD_COLS; i++) {
    digitalWrite(cols[i], HIGH);
  }
  return KBD_KEY_NONE;
}

#endif//KBD_D_MATRIX
