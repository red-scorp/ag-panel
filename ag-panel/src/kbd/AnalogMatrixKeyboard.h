/*!
  \file AnalogMatrixKeyboard.h
  \brief AG-Panel Project analog keypad keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultAnalogMatrixPin = A0;

class AnalogMatrixKeyboard: public AbstractKeyboard {

public:
  AnalogMatrixKeyboard(uint8_t Columns, uint8_t Raws, const uint16_t *Array, uint8_t Pin = DefaultAnalogMatrixPin): AbstractKeyboard(), m_Columns(Columns), m_Raws(Raws), m_Array(Array), m_Pin(Pin) { Init(); }
  virtual ~AnalogMatrixKeyboard() { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_Columns;
  uint8_t m_Raws;
  const uint16_t *m_Array;
  uint8_t m_Pin;

private:
  bool Init();
  void Exit();
};
