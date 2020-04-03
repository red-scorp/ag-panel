/*!
  \file I2CPCF8574TextLCD.h
  \brief AG-Panel Project I2C 4-bit text (hd44780) LCD interface
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractTextLCD.h"

/*!
  \brief I2C Text LCD class

  This class implements a 4-bit text LCD display based on HD44780 and connected
  with a help of PCF8574(T/AT) I2C 8-bit digital I/O expander chip.
  This class implements it's own backlight control.
 */
class I2CPCF8574TextLCD: public AbstractTextLCD {

public:
  I2CPCF8574TextLCD(
    uint8_t Columns,            /*!< Number of columns of the text LCD */
    uint8_t Rows,               /*!< Number of rows of the text LCD */
    uint8_t I2CAddress          /*!< I2C address of digital I/O expander chip */
  ): AbstractTextLCD(nullptr, Columns, Rows),
    m_I2CAddress(I2CAddress),
    m_Lowlevel(nullptr) { Init(); }
  virtual ~I2CPCF8574TextLCD() override { Exit(); }

  virtual void SetBacklight(bool on) override;
  virtual void SetBacklight(uint8_t brightness) override;
  virtual void SetBacklight(uint8_t red, uint8_t green, uint8_t blue) override;
  virtual void SetBacklight(uint32_t rgb) override;

  virtual void Clear() override;
  virtual void SetCursor(uint8_t column, uint8_t row) override;
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
