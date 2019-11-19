/*!
  \file HardwareUART.cpp
  \brief AG-Panel Project direct hardware UART implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "HardwareUART.h"
#include <HardwareSerial.h>

static HardwareSerial *sp_UART;       /*!< Pointer to a HardwareSerial class instance */

/*!
  \brief Initialization of hardware UART
  Initialize hardware UART and set baud rate.
  \return true
 */
bool HardwareUART::Init() {
  if(m_Port == 0)
    sp_UART = &Serial;
#if defined(HAVE_HWSERIAL1)
  else if(m_Port == 1)
    sp_UART = &Serial1;
#endif
#if defined(HAVE_HWSERIAL2)
  else if(m_Port == 2)
    sp_UART = &Serial2;
#endif
#if defined(HAVE_HWSERIAL3)
  else if(m_Port == 3)
    sp_UART = &Serial3;
#endif
  else
    for(;;); /* TODO: Add something like exception here! */
  sp_UART->begin(m_BaudRate);
  return true;
}

/*!
  \brief Deinitialization of hardware UART
 */
void HardwareUART::Exit() {
}

/*!
  \brief Write a character to hardware UART
  \returns Number of bytes written to hardware UART
 */
uint8_t HardwareUART::PutCh(
  uint8_t txbyte      /*!< Character to be writte to hardware UART */
) {
  return sp_UART->write(txbyte);
}

/*!
  \brief Read a character from hardware UART
  \returns Charecter (byte) read from hardware UART
 */
uint8_t HardwareUART::GetCh() {
  while(Available() == 0) {
    yield();
  }

  return sp_UART->read();
}

/*!
  \brief Check number of bytes in hardware UART buffer
  \returns number of bytes stored in buffer of hardware UART
 */
uint32_t HardwareUART::Available() {
  return sp_UART->available();
}
