/*!
  \file AbstractUART.h
  \brief AG-Panel Project abstract UART interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"

const uint32_t DefaultUARTBaudRate = 9600;    /*!< Default baud rate value used if none is specified.*/

/*!
  \brief Abstract UART class

  This is a base class for all UART implementations.
  It defines only a base interface of UART used by the rest of a project code.
 */
class AbstractUART {

public:
  explicit AbstractUART(
    uint32_t BaudRate = DefaultUARTBaudRate /*!< Baud rate of an UART */
  ): m_BaudRate(BaudRate) { Init(); }
  virtual ~AbstractUART() { Exit(); }

  virtual uint8_t PutCh(uint8_t txbyte) = 0;
  virtual uint8_t GetCh() = 0;
  virtual void Prefill() {}
  virtual uint32_t Available() { return 0; }
  virtual uint32_t GetBaudRate() const { return m_BaudRate; }

  virtual void PutStr(char *str) { while(*str != '\0') PutCh(*str++); }

protected:
  uint32_t m_BaudRate;  /*!< UART baud rate */

private:
  bool Init() { return true; }
  void Exit() {}
};
