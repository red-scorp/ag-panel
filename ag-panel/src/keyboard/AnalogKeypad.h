/*!
  \file AnalogKeypad.h
  \brief AG-Panel Project analog keypad keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultAnalogKeypadDataPin = A0;    /*!< Default input analog pin */

/*!
  \brief Analog Keypad class

  This class implements analog keypad based on several buttons connected with different resistors.
 */
class AnalogKeypad: public AbstractKeyboard {

public:
  AnalogKeypad(
    uint8_t DataPin = DefaultAnalogKeypadDataPin    /*!< Keypad input analog pin */
  ): AbstractKeyboard(),
    m_DataPin(DataPin) { Init(); }
  virtual ~AnalogKeypad() override { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_DataPin;    /*!< Keypad input analog pin */

private:
  bool Init();
  void Exit();
};
