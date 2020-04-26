/*!
  \file RawSerialProtocol.h
  \brief AG-Panel Project raw serial protocol interface
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractProtocol.h"

/*!
  \brief Raw Serial class

  This class implements a raw serial (debug) protocol.
 */
class RawSerialProtocol: public AbstractProtocol {

public:
  explicit RawSerialProtocol(
    AbstractUART *UART,           /*!< Pointer to UART implementation */
    AbstractLCD *LCD,             /*!< Pointer to LCD implementation */
    AbstractKeyboard *Keyboard    /*!< Pointer to keyboard implementation */
  ): AbstractProtocol(UART, LCD, Keyboard),
    m_XPos(0),
    m_YPos(0) { Init(); }
  virtual ~RawSerialProtocol() { Exit(); }

  virtual void Loop() override;
  virtual void Yield() override;

protected:

private:
  uint32_t m_XPos;      /*!< Current X postion on display */
  uint32_t m_YPos;      /*!< Current Y postion on display */
  bool Init();
  void Exit();
};
