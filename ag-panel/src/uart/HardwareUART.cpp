/*!
  \file HardwareUART.cpp
  \brief AG-Panel Project direct hardware UART implementation
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "HardwareUART.h"
#include <HardwareSerial.h>

#if defined(ARDUINO_ARCH_SAMD)
#include <USB/CDC.h>
#endif

/*!
  \brief Initialization of hardware UART

  Initialize hardware UART and set baud rate.
  \return true
 */
bool HardwareUART::Init() {
  if(false)
    for(;;); /* TODO: Add something like exception here! */
#if defined(HAVE_HWSERIAL0)
  else if(m_Port == 0)
    m_Lowlevel = &Serial;
#endif
#if defined(HAVE_HWSERIAL1)
  else if(m_Port == 1)
    m_Lowlevel = &Serial1;
#endif
#if defined(HAVE_HWSERIAL2)
  else if(m_Port == 2)
    m_Lowlevel = &Serial2;
#endif
#if defined(HAVE_HWSERIAL3)
  else if(m_Port == 3)
    m_Lowlevel = &Serial3;
#endif
#if defined(ARDUINO_ARCH_SAMD)
  else if(m_Port == 4) {
    m_Lowlevel = &SerialUSB;
    while(!SerialUSB);
  }
#endif
  else
    for(;;); /* TODO: Add something like exception here! */
  HardwareSerial *p_UART = reinterpret_cast<HardwareSerial*>(m_Lowlevel);
  p_UART->begin(m_BaudRate);
  return true;
}

/*!
  \brief Deinitialization of hardware UART
 */
void HardwareUART::Exit() {
  m_Lowlevel = nullptr;
}

/*!
  \brief Write a character to hardware UART

  \returns Number of bytes written to hardware UART
 */
uint8_t HardwareUART::PutCh(
  uint8_t txbyte      /*!< Character to be writte to hardware UART */
) {
  HardwareSerial *p_UART = reinterpret_cast<HardwareSerial*>(m_Lowlevel);
  return p_UART->write(txbyte);
}

/*!
  \brief Read a character from hardware UART

  \returns Charecter (byte) read from hardware UART
 */
uint8_t HardwareUART::GetCh() {
  HardwareSerial *p_UART = reinterpret_cast<HardwareSerial*>(m_Lowlevel);
  while(Available() == 0) {
    yield();
  }

  return p_UART->read();
}

/*!
  \brief Check number of bytes in hardware UART buffer

  \returns Number of bytes stored in buffer of hardware UART
 */
uint32_t HardwareUART::Available() {
  HardwareSerial *p_UART = reinterpret_cast<HardwareSerial*>(m_Lowlevel);
  return p_UART->available();
}
