/*!
  \file I2CRGBKeypad.cpp
  \brief AG-Panel Project I2C RGB keypad keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"
#include "I2CRGBKeypad.h"

#include <Adafruit_RGBLCDShield.h>
extern Adafruit_RGBLCDShield rgb_lcd; /* defined in lcd_i2c_rgb.cpp */

bool I2CRGBKeypad::Init() {
  /* The RGB Keypad is already initialized in lcd_i2c_rgb.cpp */
  return true;
}

void I2CRGBKeypad::Exit() {
}

uint8_t I2CRGBKeypad::GetKey() {

  uint8_t buttons = rgb_lcd.readButtons();

  if(buttons & BUTTON_UP)
    return KeyDefaultUp;
  if(buttons & BUTTON_DOWN)
    return KeyDefaultDown;
  if(buttons & BUTTON_LEFT)
    return KeyDefaultLeft;
  if(buttons & BUTTON_RIGHT)
    return KeyDefaultRight;
  if(buttons & BUTTON_SELECT)
    return KeyDefaultSelect;

  return KeyNone;
}
