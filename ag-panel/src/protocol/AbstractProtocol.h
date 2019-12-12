/*!
  \file AbstractProtocol.h
  \brief AG-Panel Project abstract protocol interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "../uart/AbstractUART.h"
#include "../lcd/AbstractLCD.h"
#include "../keyboard/AbstractKeyboard.h"

class AbstractProtocol {

public:
  AbstractProtocol(AbstractUART *UART, AbstractLCD *LCD, AbstractKeyboard *Keyboard): m_UART(UART), m_LCD(LCD), m_Keyboard(Keyboard) { Init(); }
  virtual ~AbstractProtocol() { Exit(); }

  virtual void Loop() = 0;
  virtual void Yield() = 0;

protected:
  AbstractUART *m_UART;
  AbstractLCD *m_LCD;
  AbstractKeyboard *m_Keyboard;

private:
  bool Init() { return true; }
  void Exit() {}
};
