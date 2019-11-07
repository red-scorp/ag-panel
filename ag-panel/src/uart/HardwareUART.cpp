/*!
  \file HardwareUART.cpp
  \brief AG-Panel Project direct hardware UART implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "HardwareUART.h"
#include <HardwareSerial.h>

/*!
  \brief Initialization of hardware UART
  Initialize hardware UART and set baud rate.
  \return true
 */
bool HardwareUART::Init() {
  Serial.begin(m_BaudRate);
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
  return Serial.write(txbyte);
}

/*!
  \brief Read a character from hardware UART
  \returns Charecter (byte) read from hardware UART
 */
uint8_t HardwareUART::GetCh() {
  while(Available() == 0) {
    yield();
  }

  return Serial.read();
}

/*!
  \brief Check number of bytes in hardware UART buffer
  \returns number of bytes stored in buffer of hardware UART
 */
uint32_t HardwareUART::Available() {
  return Serial.available();
}
