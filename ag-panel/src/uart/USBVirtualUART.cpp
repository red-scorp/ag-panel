/*!
  \file USBVirtualUART.cpp
  \brief AG-Panel Project direct USB virtual UART implementation
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "USBVirtualUART.h"

/* TODO: add also STM32's implementation (USBSerial.h) */

#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM)

#if defined(ARDUINO_ARCH_SAMD)
#include <USB/CDC.h>
#elif defined(ARDUINO_ARCH_SAM)
#include <USB/USBAPI.h>
#endif

/*!
  \brief Initialization of USB virtual UART

  Initialize USB virtual UART and set baud rate.
  \return true
 */
bool USBVirtualUART::Init() {
  m_Lowlevel = &SerialUSB;
  while(!SerialUSB);
  Serial_ *p_UART = reinterpret_cast<Serial_*>(m_Lowlevel);
  p_UART->begin(m_BaudRate);
  return true;
}

/*!
  \brief Deinitialization of USB virtual UART
 */
void USBVirtualUART::Exit() {
  m_Lowlevel = nullptr;
}

/*!
  \brief Write a character to USB virtual UART

  \returns Number of bytes written to USB virtual UART
 */
uint8_t USBVirtualUART::PutCh(
  uint8_t txbyte      /*!< Character to be writte to USB virtual UART */
) {
  Serial_ *p_UART = reinterpret_cast<Serial_*>(m_Lowlevel);
  return p_UART->write(txbyte);
}

/*!
  \brief Read a character from USB virtual UART

  \returns Charecter (byte) read from USB virtual UART
 */
uint8_t USBVirtualUART::GetCh() {
  Serial_ *p_UART = reinterpret_cast<Serial_*>(m_Lowlevel);
  while(Available() == 0) {
    yield();
  }

  return p_UART->read();
}

/*!
  \brief Check number of bytes in USB virtual UART buffer

  \returns Number of bytes stored in buffer of USB virtual UART
 */
uint32_t USBVirtualUART::Available() {
  Serial_ *p_UART = reinterpret_cast<Serial_*>(m_Lowlevel);
  return p_UART->available();
}

#else
#warning 'USBVirtualUART' is not implemented for your platform. Use 'HardwareUART' or 'NoneUART' instead!
#endif //SAMD || SAM
