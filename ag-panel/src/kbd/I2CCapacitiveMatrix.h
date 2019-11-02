/*!
  \file I2CCapacitiveMatrix.h
  \brief AG-Panel Project I2C capacitive matrix keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultI2CCapacitiveMatrixI2CAddress = 0x5A;

class I2CCapacitiveMatrix: public AbstractKeyboard {

public:
  I2CCapacitiveMatrix(uint8_t Columns, uint8_t Rows, uint8_t I2CAddress = DefaultI2CCapacitiveMatrixI2CAddress): AbstractKeyboard(), m_Columns(Columns), m_Rows(Rows), m_I2CAddress(I2CAddress) { Init(); }
  virtual ~I2CCapacitiveMatrix() override { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_Columns;
  uint8_t m_Rows;
  uint8_t m_I2CAddress;

private:
  bool Init();
  void Exit();
};
