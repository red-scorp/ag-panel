/*!
  \file SoftwareUART.cpp
  \brief AG-Panel Project direct software UART implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "SoftwareUART.h"

#if defined(__AVR__)
#include <SoftwareSerial.h>

/* TODO: make it multyinstance friendly */
static SoftwareSerial *sp_UART;       /*!< Pointer to a SoftwareSerial class instance */

/*!
  \brief Initialization of software UART
  Initialize software UART and set baud rate.
  \return true
 */
bool SoftwareUART::Init() {
  sp_UART = new SoftwareSerial(m_RxPin, m_TxPin);
  sp_UART->begin(m_BaudRate);
  return true;
}

/*!
  \brief Deinitialization of software UART
 */
void SoftwareUART::Exit() {
}

/*!
  \brief Write a character to software UART
  \returns Number of bytes written to software UART
 */
uint8_t SoftwareUART::PutCh(
  uint8_t txbyte      /*!< Character to be writte to software UART */
) {
  return sp_UART->write(txbyte);
}

/*!
  \brief Read a character from software UART
  \returns Charecter (byte) read from software UART
 */
uint8_t SoftwareUART::GetCh() {
  while(Available() == 0) {
    yield();
  }

  return sp_UART->read();
}

/*!
  \brief Check number of bytes in software UART buffer
  \returns number of bytes stored in buffer of software UART
 */
uint32_t SoftwareUART::Available() {
  return sp_UART->available();
}
#endif //__AVR__
