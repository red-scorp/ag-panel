/*!
  \file kbd_i2c_c_matrix.cpp
  \brief AG-Panel Project I2C capacitive matrix Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if defined(KBD_I2C_C_MATRIX)

#if !defined(KBD_I2C_ADDR)
#error You should define KBD_I2C_ADDR for KBD_I2C_C_MATRIX!
#endif

#include <Adafruit_MPR121.h>
Adafruit_MPR121 kbd;

/*! \brief Initialization of keyboard
 */
void kbd_init() {
  kbd.begin();
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
  const uint16_t watch_mask = (uint16_t)(1l << (KBD_COLS * KBD_ROWS + 1)) - 1; /* watch only lower CxR bits, ignore rest */
  static uint16_t last_touched = 0;
  uint16_t touched = kbd.touched() & watch_mask;
  uint16_t pressed = (touched ^ last_touched) & touched;
  uint16_t released = (touched ^ last_touched) & last_touched;
  last_touched ^= released; /* remove all released keys */
  if(pressed != 0) {
    for(uint8_t i = 0; i < (KBD_COLS * KBD_ROWS); i++) {
      if(pressed & (1 << i)) {
        last_touched ^= (1 << i); /* remember only one pressed key we are going to send to a host */
        uint8_t c = i % KBD_COLS;
        uint8_t r = i / KBD_COLS;
        return KBD_KEY(c, r);
      }
    }
  }

  return KBD_KEY_NONE;
}

#endif//LCD_I2C_RGB
