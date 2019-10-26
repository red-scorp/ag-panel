/*!
  \file AnalogKeypadKeyboard.h
  \brief AG-Panel Project analog keypad keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultAnalogKeypadDataPin = A0;

class AnalogKeypad: public AbstractKeyboard {

public:
  AnalogKeypad(uint8_t DataPin = DefaultAnalogKeypadDataPin): AbstractKeyboard(), m_DataPin(DataPin) { Init(); }
  virtual ~AnalogKeypad() { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_DataPin;

private:
  bool Init();
  void Exit();
};
