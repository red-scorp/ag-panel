/*!
  \file I2CRGBKeypad.h
  \brief AG-Panel Project I2C RGB keypad keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/*!
  \brief I2C RGB Keypad class
  This class implements RGB display keypad attached with I2C MCP23017 I/O expander controller.
 */
class I2CRGBKeypad: public AbstractKeyboard {

public:
  I2CRGBKeypad(): AbstractKeyboard() { Init(); }
  virtual ~I2CRGBKeypad() override { Exit(); }

  virtual uint8_t GetKey() override;

protected:

private:
  bool Init();
  void Exit();
};
