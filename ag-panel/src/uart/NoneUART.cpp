/*!
  \file NoneUART.cpp
  \brief AG-Panel Project none UART implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "NoneUART.h"

/*!
  \brief Initialization of none UART

  Initialize none UART.
  \return true
 */
bool NoneUART::Init() {
  return true;
}

/*!
  \brief Deinitialization of none UART
 */
void NoneUART::Exit() {
}

/*!
  \brief Write a character to none UART

  \returns Number of bytes written to hardware UART
 */
uint8_t NoneUART::PutCh(
  uint8_t txbyte      /*!< Character to be writte to hardware UART */
) {
  return 1;
}

/*!
  \brief Read a character from none UART

  \returns Charecter (byte) read from hardware UART
 */
uint8_t NoneUART::GetCh() {

  while(true) {
    yield();
  }

  return 0;
}

/*!
  \brief Check number of bytes in none UART buffer

  \returns Number of bytes stored in buffer of hardware UART
 */
uint32_t NoneUART::Available() {
  return 0;
}
