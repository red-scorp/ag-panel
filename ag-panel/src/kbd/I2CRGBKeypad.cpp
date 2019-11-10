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
extern Adafruit_RGBLCDShield *gp_I2CRGBLCD; /* Defined in I2CRGBTextLCD.cpp */

/*!
  \brief Initialization of I2C RGB keypad
  \returns true
 */
bool I2CRGBKeypad::Init() {
  /* The RGB Keypad is already initialized in I2CRGBTextLCD.cpp */
  return true;
}

/*!
  \brief Deinitialisation of I2C RGB keypad class
 */
void I2CRGBKeypad::Exit() {
}

/*!
  \brief Get a key of I2C RGB keypad
  Reads key state from I2C controller to find out what key has been pressed.
  \returns #KeyNone if no new actions detected, else a key code
 */
uint8_t I2CRGBKeypad::GetKey() {

  uint8_t buttons = gp_I2CRGBLCD->readButtons();

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
