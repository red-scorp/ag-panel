/*!
  \file SoftwareUART.h
  \brief AG-Panel Project direct software UART interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"

/*!
  \brief Software UART class
  This is a class which implements software UART of arduino boards.
  This class works with AVR ICUs only (for now).
 */
class SoftwareUART: public AbstractUART {

public:
  SoftwareUART(
    uint32_t BaudRate,    /*!< Baud rate of an UART */
    uint8_t RxPin,        /*!< Receive data UART pin */
    uint8_t TxPin         /*!< Transmit data UART pin */
  ): AbstractUART(BaudRate),
    m_RxPin(RxPin),
    m_TxPin(TxPin),
    m_Lowlevel(nullptr) { Init(); }
  virtual ~SoftwareUART() override { Exit(); }

  virtual uint8_t PutCh(uint8_t txbyte) override;
  virtual uint8_t GetCh() override;
  virtual uint32_t Available() override;

protected:
  uint8_t m_RxPin;        /*!< Receive data UART pin */
  uint8_t m_TxPin;        /*!< Transmit data UART pin */

private:
  void *m_Lowlevel;       /*!< Pointer to Low-Level Serial class */
  bool Init();
  void Exit();
};
