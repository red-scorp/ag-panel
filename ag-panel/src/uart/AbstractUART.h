/*!
  \file AbstractUART.h
  \brief AG-Panel Project abstract UART interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"

/*!
  \brief Default baud rate value used if none is specified.
 */
const auto DefaultBaudRate = 9600;

/*!
  \brief Abstract UART class
  This is a base class for all UART implementations.
  It defines only a base interface of UART used by rest of a project code.
 */
class AbstractUART {

public:
  AbstractUART(
    uint32_t BaudRate = DefaultBaudRate /*!< Baud rate of an UART */
  ): m_BaudRate(BaudRate) { Init(); }
  virtual ~AbstractUART() { Exit(); }

  virtual uint8_t PutCh(uint8_t txbyte) = 0;
  virtual uint8_t GetCh() = 0;
  virtual void Prefill() {}
  virtual uint32_t Available() { return 0; }
  uint32_t GetBaudRate() const { return m_BaudRate; }

protected:
  uint32_t m_BaudRate;  /*!< UART baud rate */

private:
  bool Init() { return true; }
  void Exit() {}
};