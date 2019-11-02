/*!
  \file AbstractLCD.h
  \brief AG-Panel Project abstract LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractBacklight.h"

class AbstractLCD {

public:
  AbstractLCD(AbstractBacklight *Backlight = nullptr): m_Backlight(Backlight) { Init(); }
  virtual ~AbstractLCD() { Exit(); }

  virtual void SetBacklight(bool on) { m_Backlight->SetOn(on); }
  virtual void SetBacklight(uint8_t brightness) { m_Backlight->SetBrightness(brightness); }
  virtual void SetBacklight(uint8_t red, uint8_t green, uint8_t blue) { m_Backlight->SetRGB(red, green, blue); }
  virtual void SetBacklight(uint32_t rgb) { m_Backlight->SetRGB(rgb); }

  virtual void Clear() = 0;
  virtual void SetCursor(uint8_t column, uint8_t row) = 0;
  virtual void Print(const char *str) = 0;

protected:
  AbstractBacklight * m_Backlight;

private:
  bool Init() { return true; }
  void Exit() {}
};
