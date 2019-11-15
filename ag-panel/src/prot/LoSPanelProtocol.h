/*!
  \file LoSPanelProtocol.h
  \brief AG-Panel Project LoS-panel protocol interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractProtocol.h"
#include "../lcd/AbstractTextLCD.h"

class LoSPanelProtocol: public AbstractProtocol {

public:
  LoSPanelProtocol(AbstractUART *UART, AbstractTextLCD *TextLCD, AbstractKeyboard *Keyboard): AbstractProtocol(UART, TextLCD, Keyboard), m_TextLCD(TextLCD) { Init(); }
  virtual ~LoSPanelProtocol() { Exit(); }

  virtual void Loop() override;
  virtual void Yield() override;

protected:
  AbstractTextLCD *m_TextLCD;

private:
  uint32_t m_LCDLastTxMicros;     /*!< Last LCD transfer microseconds time stamp value */
  bool Init();
  void Exit();
  void WaitFromLastTx(uint32_t WaitMicros);
  void StampLastTx();
};
