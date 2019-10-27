/*!
  \file DigitalMatrix.h
  \brief AG-Panel Project digital keypad keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

class DigitalMatrix: public AbstractKeyboard {

public:
  DigitalMatrix(uint8_t Columns, uint8_t Rows, const uint8_t *CPinsArray, const uint8_t *RPinsArray): AbstractKeyboard(), m_Columns(Columns), m_Rows(Rows), m_CPinsArray(CPinsArray), m_RPinsArray(RPinsArray) { Init(); }
  virtual ~DigitalMatrix() { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_Columns;
  uint8_t m_Rows;
  const uint8_t *m_CPinsArray;
  const uint8_t *m_RPinsArray;

private:
  bool Init();
  void Exit();
};
