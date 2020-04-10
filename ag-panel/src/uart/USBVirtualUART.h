/*!
  \file USBVirtualUART.h
  \brief AG-Panel Project direct USB virtual UART interface
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"

/*!
  \brief USB virtual UART class

  This is a class which implements USB virtual UART of arduino boards.
 */
class USBVirtualUART: public AbstractUART {

public:
  explicit USBVirtualUART(
    uint32_t BaudRate = DefaultUARTBaudRate   /*!< Baud rate of an UART */
  ): AbstractUART(BaudRate),
    m_Lowlevel(nullptr) { Init(); }
  virtual ~USBVirtualUART() override { Exit(); }

  virtual uint8_t PutCh(uint8_t txbyte) override;
  virtual uint8_t GetCh() override;
  virtual uint32_t Available() override;

protected:

private:
  void *m_Lowlevel;       /*!< Pointer to Low-Level Serial class */
  bool Init();
  void Exit();
};
