/*!
  \file TextLoggingUART.h
  \brief AG-Panel Project text logging UART interface
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"

const uint8_t NumbersBaseBinary = 2;
const uint8_t NumbersBaseOctal = 8;
const uint8_t NumbersBaseDecimal = 10;
const uint8_t NumbersBaseHexadecimal = 16;
const uint8_t DefaultNumbersBase = NumbersBaseHexadecimal;

/*!
  \brief Text Logging UART class

  This is a class which implements logging of UART communication to another UART in text form.
 */
class TextLoggingUART: public AbstractUART {

public:
  explicit TextLoggingUART(
    AbstractUART *RealUART,       /*!< Real (communication) UART */
    AbstractUART *DebugUART,      /*!< Debug (logging) UART */
    uint8_t NumbersBase = NumbersBaseHexadecimal, /*!< Base to convert numbers */
    uint8_t LineWrap = 1          /*!< Flag enaling wraping a line */
  ): AbstractUART(0),
    m_RealUART(RealUART),
    m_DebugUART(DebugUART),
    m_NumbersBase(NumbersBase),
    m_LineWrap(LineWrap),
    m_Direction(2),
    m_NumberLength(0),
    m_LeadingZeros(0),
    m_WrapLineLength(0),
    m_CurrentLineLength(0) { Init(); }
  virtual ~TextLoggingUART() override { Exit(); }

  virtual uint8_t PutCh(uint8_t txbyte) override;
  virtual uint8_t GetCh() override;
  virtual uint32_t Available() override;
  virtual uint32_t GetBaudRate() const override;

protected:
  AbstractUART *m_RealUART;       /*!< Real (communication) UART */
  AbstractUART *m_DebugUART;      /*!< Debug (logging) UART */
  uint8_t m_NumbersBase;          /*!< Base to convert numbers */
  uint8_t m_LineWrap;             /*!< Flag enaling wraping a line */

private:
  uint8_t m_Direction;            /*!< Direction of communication took last time */
  uint8_t m_NumberLength;         /*!< Number of digits in number (for one byte) */
  uint8_t m_LeadingZeros;         /*!< Leading zeros in number should be printed */
  uint8_t m_WrapLineLength;       /*!< Line wrapping length */
  uint8_t m_CurrentLineLength;    /*!< Current line length */
  void PrintByte(uint8_t byte, uint8_t direction);
  bool Init();
  void Exit();
};
