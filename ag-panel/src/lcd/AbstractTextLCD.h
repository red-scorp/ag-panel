/*!
  \file AbstractTextLCD.h
  \brief AG-Panel Project abstract text (hd44780) LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractLCD.h"

class AbstractTextLCD: public AbstractLCD {

public:
  AbstractTextLCD(AbstractBacklight *Backlight = nullptr): AbstractLCD(Backlight) { Init(); }
  virtual ~AbstractTextLCD() { Exit(); }

  using AbstractLCD::SetBacklight;
  using AbstractLCD::Clear;
  using AbstractLCD::SetCursor;
  using AbstractLCD::Print;

  virtual void Write(uint8_t byte) = 0;
  virtual void Command(uint8_t byte) = 0;

protected:

private:
  bool Init() { return true; }
  void Exit() {}
};
