/*!
  \file I2CCapacitiveMatrix.h
  \brief AG-Panel Project I2C capacitive matrix keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultI2CCapacitiveMatrixI2CAddress = 0x5A;    /*!< Default I2C address for capacitive matrix controller */

/*!
  \brief I2C Capacitive Matrix class
  This class implements capacitive matrix based on MPR121 I2C touch controller.
 */
class I2CCapacitiveMatrix: public AbstractKeyboard {

public:
  I2CCapacitiveMatrix(
    uint8_t Columns,        /*!< Number of columns of the matrix */
    uint8_t Rows,           /*!< Number of rows of the matrix */
    uint8_t I2CAddress = DefaultI2CCapacitiveMatrixI2CAddress   /*!< I2C address of the touch controller */
  ): AbstractKeyboard(),
    m_Columns(Columns),
    m_Rows(Rows),
    m_I2CAddress(I2CAddress) { Init(); }
  virtual ~I2CCapacitiveMatrix() override { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_Columns;        /*!< Number of columns of the matrix */
  uint8_t m_Rows;           /*!< Number of rows of the matrix */
  uint8_t m_I2CAddress;     /*!< I2C address of the touch controller */

private:
  bool Init();
  void Exit();
};
