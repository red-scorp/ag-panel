/*!
  \file BufferedUART.cpp
  \brief AG-Panel Project buffered UART implementation
  \copyright (C) 2019-2022 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "BufferedUART.h"

/*!
  \brief Initialization of buffered UART

  Initialize buffered UART and allocate data buffer.
  \returns true
 */
bool BufferedUART::Init() {
  m_Buffer = new uint8_t[m_BufferSize];
  return (m_Buffer == nullptr)? false: true;
}

/*!
  \brief Deinitialization of buffered UART and deallocate data buffer
 */
void BufferedUART::Exit() {
  if(m_UART != nullptr)
    delete m_UART;
}

/*!
  \brief Write a character to real UART

  \returns Number of bytes written to real UART
 */
uint8_t BufferedUART::PutCh(
  uint8_t txbyte      /*!< Character to be written to real UART */
) {
  return m_UART->PutCh(txbyte);
}

/*!
  \brief Read a character from UART buffer

  \returns Character (byte) read from UART buffer
 */
uint8_t BufferedUART::GetCh() {
  while(FillBuffer() == 0) {
    yield();
  }

  return PushBuffer();
}

/*!
  \brief Prefill UART data buffer
 */
void BufferedUART::Prefill() {
  FillBuffer();
}

/*!
  \brief Push a character from UART data buffer

  \returns Character (byte) from top of a buffer (oldest)
 */
uint8_t BufferedUART::PushBuffer() {
  uint8_t top_byte = m_Buffer[0];

  for(uint32_t i = 1; i < m_BufferFilled; i++) {
    m_Buffer[i - 1] = m_Buffer[i];
  }

  m_BufferFilled--;
  return top_byte;
}

/*!
  \brief Fill UART data buffer from real UART

  \returns Number of bytes in UART data buffer
 */
uint8_t BufferedUART::FillBuffer() {
  while(m_BufferFilled < m_BufferSize && m_UART->Available()) {
    uint8_t rxbyte = m_UART->GetCh();
    m_Buffer[m_BufferFilled++] = rxbyte;
  }

  return m_BufferFilled;
}

/*!
  \brief Check number of bytes in UART data buffer

  \returns Number of bytes stored in UART buffer and in buffer of real UART
 */
uint32_t BufferedUART::Available() {
  return m_BufferFilled + m_UART->Available();
}
