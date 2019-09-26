/*!
  \file AbstractLCD.h
  \brief AG-Panel Project abstract LCD backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractLCDBackligt.h"

class AbstractLCD {

public:
  AbstractLCD(AbstractLCDBackligt * LCDBacklight = nullptr): m_LCDBacklight(LCDBacklight) { Init(); }
  virtual ~AbstractLCD() { Exit(); }

  virtual void SetBacklight(bool on) { m_LCDBacklight->SetBacklight(on); }
  virtual void SetBacklight(uint8_t brightness) { m_LCDBacklight->SetBacklight(brightness); }
  virtual void SetBacklight(uint8_t red, uint8_t green, uint8_t blue) { m_LCDBacklight->SetBacklight(red, green, blue); }
  virtual void SetBacklight(uint32_t rgb) { m_LCDBacklight->SetBacklight(rgb); }

  virtual void Clear() = 0;
  virtual void SetCursor(uint8_t row, uint8_t col) = 0;
  virtual void Print(char *str) = 0;

protected:
  AbstractLCDBackligt * m_LCDBacklight;

private:
  bool Init() { return true; }
  void Exit() {}
};
