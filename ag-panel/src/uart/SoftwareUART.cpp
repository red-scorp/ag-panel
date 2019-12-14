/*!
  \file SoftwareUART.cpp
  \brief AG-Panel Project direct software UART implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "SoftwareUART.h"

#if defined(__AVR__) || defined(STM32F0xx) || defined(STM32F1xx) || defined(STM32F2xx) || defined(STM32F3xx) || defined(STM32F4xx) || defined(STM32F7xx) || defined(STM32G0xx) || defined(STM32G4xx) || defined(STM32H7xx) || defined(STM32L0xx) || defined(STM32L1xx) || defined(STM32L4xx) || defined(STM32WBxx)
#include <SoftwareSerial.h>

/*!
  \brief Initialization of software UART

  Initialize software UART and set baud rate.
  \return true
 */
bool SoftwareUART::Init() {
  m_Lowlevel = new SoftwareSerial(m_RxPin, m_TxPin);
  SoftwareSerial *p_UART = (SoftwareSerial*)m_Lowlevel;
  p_UART->begin(m_BaudRate);
  return true;
}

/*!
  \brief Deinitialization of software UART
 */
void SoftwareUART::Exit() {
  SoftwareSerial *p_UART = (SoftwareSerial*)m_Lowlevel;
  if(p_UART != nullptr)
    delete p_UART;
  m_Lowlevel = nullptr;
}

/*!
  \brief Write a character to software UART

  \returns Number of bytes written to software UART
 */
uint8_t SoftwareUART::PutCh(
  uint8_t txbyte      /*!< Character to be writte to software UART */
) {
  SoftwareSerial *p_UART = (SoftwareSerial*)m_Lowlevel;
  return p_UART->write(txbyte);
}

/*!
  \brief Read a character from software UART

  \returns Charecter (byte) read from software UART
 */
uint8_t SoftwareUART::GetCh() {
  SoftwareSerial *p_UART = (SoftwareSerial*)m_Lowlevel;
  while(Available() == 0) {
    yield();
  }

  return p_UART->read();
}

/*!
  \brief Check number of bytes in software UART buffer

  \returns Number of bytes stored in buffer of software UART
 */
uint32_t SoftwareUART::Available() {
  SoftwareSerial *p_UART = (SoftwareSerial*)m_Lowlevel;
  return p_UART->available();
}

#else
#warning 'SoftwareUART' is not implemented for your platform. Use 'HardwareUART' or 'NoneUART' instead!
#endif //__AVR__ || STM32
