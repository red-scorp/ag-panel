/*!
  \file RawSerialProtocol.cpp
  \brief AG-Panel Project raw serial protocol implmentation
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "RawSerialProtocol.h"

/* Protocol commands definition */
const uint8_t RawSerialProtocolEndOfBuffer = '\n';    /*!< End of buffer code, comes from host to target */

/*!
  \brief Initialization of rawserial protocol

  Configures rawserial protocol class.
  \returns true
 */
bool RawSerialProtocol::Init() {
  return true;
}

/*!
  \brief Deinitialisation of rawserial protocol class
 */
void RawSerialProtocol::Exit() {
}

/*!
  \brief Main loop of rawserial protocol

  This function reads UART and interpret the input based on rawserial protocol rules.
 */
void RawSerialProtocol::Loop() {
  uint8_t rxbyte = m_UART->GetCh();
  char ch = rxbyte;

  if(rxbyte == RawSerialProtocolEndOfBuffer) {
    m_LCD->SetCursor(0, 0);
  } else {
    m_LCD->Print(ch);
  }
}

/*!
  \brief Background job of rawserial protocol

  This function reads keyboard input and puts it to UART.
 */
void RawSerialProtocol::Yield() {
  static uint8_t old_key = KeyNone;
  uint8_t key = m_Keyboard->GetKey();

  if(old_key != key)
    old_key = key;
  else
    return;

  if(key != KeyNone) {
    // uint8_t txbyte = LoSPanelKeypadCode(key >> 2, key & 0x3);
    // m_UART->PutCh(LoSPanelProtocolKeypad);
    // m_UART->PutCh(txbyte);
  }

  m_UART->Prefill();
}
