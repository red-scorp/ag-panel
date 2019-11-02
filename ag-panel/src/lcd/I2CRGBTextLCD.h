/*!
  \file I2CRGBTextLCD.h
  \brief AG-Panel Project I2C RGB keypad's text (hd44780) LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractTextLCD.h"

const uint32_t DefaultI2CRGBTextLCDDefaultColor = DefaultBacklightRGBColor;

class I2CRGBTextLCD: public AbstractTextLCD {

public:
  I2CRGBTextLCD(uint8_t Columns, uint8_t Rows, uint8_t I2CAddress, uint32_t DefaultColor = DefaultI2CRGBTextLCDDefaultColor): AbstractTextLCD(nullptr), m_Columns(Columns), m_Rows(Rows), m_I2CAddress(I2CAddress), m_DefaultColor(DefaultColor) { Init(); }
  virtual ~I2CRGBTextLCD() { Exit(); }

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
  uint8_t m_Columns;
  uint8_t m_Rows;
  uint8_t m_I2CAddress;
  uint32_t m_DefaultColor;

private:
  bool Init();
  void Exit();
};
