/*!
  \file kbd_a_matrix.cpp
  \brief AG-Panel Project Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if 0 //defined(KBD_A_MATRIX)

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
  /* No initialization for analog pins needed */
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
  static const uint16_t data_array[KBD_ROWS * KBD_COLS] = KBD_DATA_ARRAY;
  uint16_t data = analogRead(KBD_PIN_DATA);
  for(uint8_t c = 0 ; c < KBD_COLS; c++)
    for(uint8_t r = 0 ; r < KBD_ROWS; r++) {
      if(data >= data_array[r * KBD_COLS + c] - KBD_PIN_DATA &&
        data <= data_array[r * KBD_COLS + c] + KBD_PIN_DATA) {
        return KBD_KEY(c, r);
      }
    }
  return KBD_KEY_NONE;
}

#endif//KBD_A_MATRIX
