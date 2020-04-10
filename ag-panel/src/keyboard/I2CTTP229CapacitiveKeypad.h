/*!
  \file I2CTTP229CapacitiveKeypad.h
  \brief AG-Panel Project I2C TTP229 capacitive matrix keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultI2CTTP229CapacitiveKeypadI2CAddress = 0x5A;    /*!< Default I2C address for capacitive matrix controller */

/*!
  \brief I2C TTP229 Capacitive Matrix class

  This class implements capacitive matrix based on TTP229 I2C touch controller.
 */
class I2CTTP229CapacitiveKeypad: public AbstractKeyboard {

public:
  explicit I2CTTP229CapacitiveKeypad(
    uint8_t Number,       /*!< Number of keys in keys in keypad */
    uint8_t I2CAddress = DefaultI2CTTP229CapacitiveKeypadI2CAddress   /*!< I2C address of the touch controller */
  ): AbstractKeyboard(),
    m_Number(Number),
    m_I2CAddress(I2CAddress),
    m_Lowlevel(nullptr) { Init(); }
  virtual ~I2CTTP229CapacitiveKeypad() override { Exit(); }

  virtual uint8_t GetKey() override;
  virtual uint8_t GetKeyCount() override;

protected:
  uint8_t m_Number;       /*!< Number of keys in keys in keypad */
  uint8_t m_I2CAddress;   /*!< I2C address of the touch controller */

private:
  void *m_Lowlevel;       /*!< Pointer to Low-Level Kbd class */
  bool Init();
  void Exit();
};
