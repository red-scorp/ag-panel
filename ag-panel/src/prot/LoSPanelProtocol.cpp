/*!
  \file LoSPanelProtocol.cpp
  \brief AG-Panel Project LoS-panel protocol implmentation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "LoSPanelProtocol.h"

/* Protocol commands definition */
const uint8_t LoSPanelProtocolInstruction = 0xFE;   /*!< Instruction code prefix, comes from host to target */
const uint8_t LoSPanelProtocolKeypad = 0xFE;        /*!< Keypad code prefix, comes from target to host */
const uint8_t LoSPanelProtocolBacklight = 0xFD;     /*!< LCD Backlight control prefix, comes from host to target */

const uint8_t LoSPanelProtocolBacklightOff = 0x00;  /*!< Enable LCD Backlight code */
const uint8_t LoSPanelProtocolBacklightOn = 0xFF;   /*!< Disable LCD Backlight code */

constexpr uint8_t LoSPanelKeypadCode(uint8_t row, uint8_t col) {
  return ((col) << 4) | (1 << (row));
}

/*!
  \brief Initialization of los-panel protocol
  Configures ...
  \note https://mlf.home.xs4all.nl/los/
  \returns true
 */
bool LoSPanelProtocol::Init() {
  m_LCDLastTxMicros = 0;
  return true;
}

/*!
  \brief Deinitialisation of los-panel protocol class
 */
void LoSPanelProtocol::Exit() {
}

/*!
  \brief Wait for given microseconds from last text LCD transfer
 */
void LoSPanelProtocol::WaitFromLastTx(
  uint32_t WaitMicros       /*!< Time in microseconds to wait */
) {
  uint32_t WaitForMicros = m_LCDLastTxMicros + WaitMicros;

  if((WaitForMicros > m_LCDLastTxMicros) && (micros() >= WaitForMicros)) /* we are already over the target time */
    return;

//  digitalWrite(LED_BUILTIN, HIGH);

  if(WaitForMicros < m_LCDLastTxMicros) { /* we have an micros() overflow */
    while(micros() > m_LCDLastTxMicros) /* first run over the maximum */
      Yield();
  }

  while(micros() < WaitForMicros) /* now wait for target time */
    Yield();

//  digitalWrite(LED_BUILTIN, LOW);
}

/*! \brief Store last LCD transfer time stamp
 */
void LoSPanelProtocol::StampLastTx() {
  m_LCDLastTxMicros = micros();
}

/*!
  \brief Main loop of los-panel protocol
  This function calls ...
 */
void LoSPanelProtocol::Loop() {
  uint8_t rxbyte = m_UART->GetCh();

  switch(rxbyte) {

  case LoSPanelProtocolInstruction:
    uint8_t nextbyte = m_UART->GetCh();
    WaitFromLastTx(nextbyte < 4? 2000: 40); /* for commands 1 - 3 wait for 2 ms, otherwise 40 us */
    m_TextLCD->Command(nextbyte);
    StampLastTx();
    break;

  case LoSPanelProtocolBacklight:
    m_TextLCD->SetBacklight(m_UART->GetCh());
    break;

  default:
    WaitFromLastTx(40);
    m_TextLCD->Write(rxbyte);
    StampLastTx();
    break;
  }
}

/*!
  \brief Background job of los-panel protocol
  This function calls ...
 */
void LoSPanelProtocol::Yield() {
  static uint8_t old_key = KeyNone;
  uint8_t key = m_Keyboard->GetKey();

  if(old_key != key)
    old_key = key;
  else
    return;

  if(key != KeyNone) {
    uint8_t txbyte = LoSPanelKeypadCode(key >> 2, key & 0x3);
    m_UART->PutCh(LoSPanelProtocolKeypad);
    m_UART->PutCh(txbyte);
  }

  m_UART->Prefill();
}
