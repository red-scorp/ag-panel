/*!
  \file TextLoggingUART.cpp
  \brief AG-Panel Project text logging UART implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "TextLoggingUART.h"

static const char s_Numbers[] = "0123456789ABCDEF";

/*!
  \brief Initialization of text logging UART
  Initialize text logging UART.
  \return true
 */
bool TextLoggingUART::Init() {

  switch(m_NumbersBase) {
  case NumbersBaseBinary:
  case NumbersBaseOctal:
  case NumbersBaseDecimal:
  case NumbersBaseHexadecimal:
    /* Everything ok. do nothing */
    break;
  default:
    m_NumbersBase = DefaultNumbersBase;
    break;
  }

  switch(m_NumbersBase) {
  case NumbersBaseBinary:
    m_NumberLength = 8;
    m_LeadingZeros = 1;
    break;
  case NumbersBaseOctal:
    m_NumberLength = 3;
    m_LeadingZeros = 1;
    break;
  case NumbersBaseDecimal:
    m_NumberLength = 3;
    m_LeadingZeros = 0;
    break;
  case NumbersBaseHexadecimal:
    m_NumberLength = 2;
    m_LeadingZeros = 1;
    break;
  }

  return true;
}

/*!
  \brief Deinitialization of text logging UART
 */
void TextLoggingUART::Exit() {
}

/*!
  \brief Write a character to text logging UART
  \returns Number of bytes written to real UART
 */
uint8_t TextLoggingUART::PutCh(
  uint8_t txbyte      /*!< Character to be writte to text logging UART */
) {
  PrintByte(txbyte, 0);
  return m_RealUART->PutCh(txbyte);
}

/*!
  \brief Read a character from text logging UART
  \returns Charecter (byte) read from real UART
 */
uint8_t TextLoggingUART::GetCh() {
  uint8_t rxbyte = m_RealUART->GetCh();
  PrintByte(rxbyte, 1);
  return rxbyte;
}

/*!
  \brief Check number of bytes in text logging UART buffer
  \returns Number of bytes stored in buffer of real UART
 */
uint32_t TextLoggingUART::Available() {
  return m_RealUART->Available();
}

/*!
  \brief Get baud rate of text logging UART
  \returns Baud rate of real UART
 */
uint32_t TextLoggingUART::GetBaudRate() const {
  return m_RealUART->GetBaudRate();
}

/*!
  \brief Print a byte
  This function prints given byte in specified format to a debug UART.
 */
void TextLoggingUART::PrintByte(
  uint8_t byte,       /*!< byte to be printed */
  uint8_t direction   /*!< firection it goes to */
) {
  char str[m_NumberLength + 1];
  char *p;

  if(m_Direction != direction) {
    m_DebugUART->PutCh('\n');
    m_DebugUART->PutCh('\r');
    m_DebugUART->PutCh(direction == 0? '>': '<');
    m_Direction = direction;
  }

  p = &str[m_NumberLength];
  *p-- = '\0';
  for(int i = 0; i < m_NumberLength; i++) {
    uint8_t digit = byte % m_NumbersBase;
    byte = byte / m_NumbersBase;
    *p-- = s_Numbers[digit];
  }

  m_DebugUART->PutCh(' ');
  for(int i = 0; i < m_NumberLength; i++) {
    if(m_LeadingZeros)
      m_DebugUART->PutCh(str[i]);
    else {
      bool meet_nonzero = false;
      if(meet_nonzero || str[i] != '\0' || i == m_NumberLength - 1) {
        m_DebugUART->PutCh(str[i]);
        meet_nonzero = true;
      }
    }
  }
}