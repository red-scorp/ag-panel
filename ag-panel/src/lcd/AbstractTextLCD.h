/*!
  \file AbstractTextLCD.h
  \brief AG-Panel Project abstract text (hd44780) LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractLCD.h"

/*!
  \brief Abstract Text LCD class
  This is a base class for all text LCD implementations.
  It defines only a base interface of text LCD used by the rest of a project code.
 */
class AbstractTextLCD: public AbstractLCD {

public:
  AbstractTextLCD(
    AbstractBacklight *Backlight = nullptr  /*!< Pointer to a backlight instance */
  ): AbstractLCD(Backlight) { Init(); }
  virtual ~AbstractTextLCD() override { Exit(); }

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
