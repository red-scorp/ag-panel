/*!
  \file AnalogMatrix.h
  \brief AG-Panel Project analog keypad keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultAnalogMatrixDataPin = A0;

class AnalogMatrix: public AbstractKeyboard {

public:
  AnalogMatrix(uint8_t Columns, uint8_t Rows, const uint16_t *DataArray, uint8_t DataPin = DefaultAnalogMatrixDataPin): AbstractKeyboard(), m_Columns(Columns), m_Rows(Rows), m_DataArray(DataArray), m_DataPin(DataPin) { Init(); }
  virtual ~AnalogMatrix() { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_Columns;
  uint8_t m_Rows;
  const uint16_t *m_DataArray;
  uint8_t m_DataPin;

private:
  bool Init();
  void Exit();
};