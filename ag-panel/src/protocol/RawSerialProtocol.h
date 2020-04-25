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
  ): AbstractProtocol(UART, LCD, Keyboard) { Init(); }
  virtual ~RawSerialProtocol() { Exit(); }

  virtual void Loop() override;
  virtual void Yield() override;

protected:

private:
  bool Init();
  void Exit();
};
