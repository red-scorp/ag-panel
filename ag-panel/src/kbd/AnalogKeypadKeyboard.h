/*!
  \file AnalogKeypadKeyboard.h
  \brief AG-Panel Project analog keypad keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultAnalogKeypadPin = A0;

class AnalogKeypadKeyboard: public AbstractKeyboard {

public:
  AnalogKeypadKeyboard(uint8_t Pin = DefaultAnalogKeypadPin): AbstractKeyboard(), m_Pin(Pin) { Init(); }
  virtual ~AnalogKeypadKeyboard() { Exit(); }

  virtual uint8_t GetKey();

protected:
  uint8_t m_Pin;

private:
  bool Init();
  void Exit();
};
