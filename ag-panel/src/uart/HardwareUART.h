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
    uint32_t BaudRate = DefaultBaudRate /*!< Baud rate of an UART */
  ): AbstractUART(BaudRate) { Init(); }
  virtual ~HardwareUART() { Exit(); }

  virtual uint8_t PutCh(uint8_t txbyte) override;
  virtual uint8_t GetCh() override;
  virtual uint32_t Available() override;

private:
  bool Init();
  void Exit();
};
