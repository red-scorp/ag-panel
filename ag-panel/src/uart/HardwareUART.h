/*!
  \file HardwareUART.h
  \brief AG-Panel Project direct hardware UART interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"

/*!
  \brief Hardware UART class

  This is a class which implements hardware UART of arduino boards.
 */
class HardwareUART: public AbstractUART {

public:
  HardwareUART(
    uint32_t BaudRate = DefaultBaudRate,  /*!< Baud rate of an UART */
    uint8_t Port = 0      /*!< Hardware UART port number */
  ): AbstractUART(BaudRate),
    m_Port(Port),
    m_Lowlevel(nullptr) { Init(); }
  virtual ~HardwareUART() override { Exit(); }

  virtual uint8_t PutCh(uint8_t txbyte) override;
  virtual uint8_t GetCh() override;
  virtual uint32_t Available() override;

protected:
  uint8_t m_Port;         /*!< Hardware UART port number */

private:
  void *m_Lowlevel;       /*!< Pointer to Low-Level Serial class */
  bool Init();
  void Exit();
};
