/*!
  \file kbd_i2c_rgb.cpp
  \brief AG-Panel Project I2C RGB keypad Keyboard code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "kbd.h"

#if defined(LCD_TEXT_I2C_RGB)

#include <Adafruit_RGBLCDShield.h>
extern Adafruit_RGBLCDShield lcd; /* defined in lcd_i2c_rgb.cpp */

/*! \brief Initialization of keyboard
 */
void kbd_init() {
  /* The RGB Keypad is already initialized in lcd_i2c_rgb.cpp */
}

/*! \brief Read current key
 */
uint8_t kbd_getkey() {
  uint8_t buttons = lcd.readButtons();
  if(buttons & BUTTON_UP)
    return KBD_KEY_UP;
  if(buttons & BUTTON_DOWN)
    return KBD_KEY_DOWN;
  if(buttons & BUTTON_LEFT)
    return KBD_KEY_LEFT;
  if(buttons & BUTTON_RIGHT)
    return KBD_KEY_RIGHT;
  if(buttons & BUTTON_SELECT)
    return KBD_KEY_SELECT;
}

#endif//LCD_I2C_RGB
