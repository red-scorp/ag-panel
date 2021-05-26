/*!
  \file USBVirtualUART.cpp
  \brief AG-Panel Project direct USB virtual UART implementation
  \copyright (C) 2020-2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "USBVirtualUART.h"

#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_STM32)

#if defined(ARDUINO_ARCH_SAMD)
#if defined(ADAFRUIT_GRAND_CENTRAL_M4) || defined(ADAFRUIT_METRO_M4_EXPRESS)
#include <USB/USBAPI.h>
#define SerialUSB Serial /* this is a hack but it's ok for now */
#else
#include <USB/CDC.h>
#endif
typedef Serial_ USBVirtualUART_Lowlevel_t;
#elif defined(ARDUINO_ARCH_SAM)
#include <USB/USBAPI.h>
typedef Serial_ USBVirtualUART_Lowlevel_t;
#elif defined(ARDUINO_ARCH_STM32)
#include <USBSerial.h>
typedef USBSerial USBVirtualUART_Lowlevel_t;
#endif

/*!
  \brief Initialization of USB virtual UART

  Initialize USB virtual UART and set baud rate.
  \returns true
 */
bool USBVirtualUART::Init() {
  m_Lowlevel = &SerialUSB;
  USBVirtualUART_Lowlevel_t *p_UART = reinterpret_cast<USBVirtualUART_Lowlevel_t*>(m_Lowlevel);
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
  uint8_t txbyte      /*!< Character to be written to USB virtual UART */
) {
  USBVirtualUART_Lowlevel_t *p_UART = reinterpret_cast<USBVirtualUART_Lowlevel_t*>(m_Lowlevel);
  return p_UART->write(txbyte);
}

/*!
  \brief Read a character from USB virtual UART

  \returns Charecter (byte) read from USB virtual UART
 */
uint8_t USBVirtualUART::GetCh() {
  USBVirtualUART_Lowlevel_t *p_UART = reinterpret_cast<USBVirtualUART_Lowlevel_t*>(m_Lowlevel);
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
  USBVirtualUART_Lowlevel_t *p_UART = reinterpret_cast<USBVirtualUART_Lowlevel_t*>(m_Lowlevel);
  return p_UART->available();
}

#else
#warning 'USBVirtualUART' is not implemented for your platform. Use 'HardwareUART' or 'NoneUART' instead!
#endif //SAMD || SAM
