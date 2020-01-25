/*!
  \file I2CAIP31068TextLCD.h
  \brief AG-Panel Project I2C 8-bit text (AIP31068) LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractTextLCD.h"

/*!
  \brief I2C Text LCD class

  This class implements a 8-bit text LCD display based on AIP31068, similar to
  HD44780 but with I2C and SPI interface.
  This class implements it's own backlight control.
 */
class I2CAIP31068TextLCD: public AbstractTextLCD {

public:
  I2CAIP31068TextLCD(
    uint8_t Columns,            /*!< Number of columns of the text LCD */
    uint8_t Rows,               /*!< Number of rows of the text LCD */
    uint8_t I2CAddress          /*!< I2C address of digital I/O expander chip */
  ): AbstractTextLCD(nullptr, Columns, Rows),
    m_I2CAddress(I2CAddress),
    m_Lowlevel(nullptr) { Init(); }
  virtual ~I2CAIP31068TextLCD() override { Exit(); }

  virtual void SetBacklight(bool on) override;
  virtual void SetBacklight(uint8_t brightness) override;
  virtual void SetBacklight(uint8_t red, uint8_t green, uint8_t blue) override;
  virtual void SetBacklight(uint32_t rgb) override;

  virtual void Clear() override;
  virtual void SetCursor(uint8_t row, uint8_t col) override;
  virtual void Print(const char *str) override;

  virtual void Write(uint8_t byte) override;
  virtual void Command(uint8_t byte) override;

protected:
  uint8_t m_I2CAddress;         /*!< I2C address of digital I/O expander chip */

private:
  void *m_Lowlevel;       /*!< Pointer to Low-Level LCD class */
  bool Init();
  void Exit();
};
