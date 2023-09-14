/** @file LoSPanelProtocol.cpp
    @brief AG-Panel Project LoS-panel protocol implementation
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "LoSPanelProtocol.h"

/* Protocol commands definition */
const uint8_t LoSPanelProtocolInstruction = 0xFE;   /**< Instruction code prefix, comes from host to target */
const uint8_t LoSPanelProtocolKeypad = 0xFE;        /**< Keypad code prefix, comes from target to host */
const uint8_t LoSPanelProtocolBacklight = 0xFD;     /**< LCD Backlight control prefix, comes from host to target */

const uint8_t LoSPanelProtocolBacklightOff = 0x00;  /**< Enable LCD Backlight code */
const uint8_t LoSPanelProtocolBacklightOn = 0xFF;   /**< Disable LCD Backlight code */

const uint32_t LosPanelProtocolLCDShortDelay = 40;  /**< Short delay in microseconds between LCD transfers (37 us by 270 kHz) */
const uint32_t LosPanelProtocolLCDLongDelay = 2000; /**< Long delay in microseconds between LCD transfers (1.52 ms by 270 kHz) */

constexpr uint8_t LoSPanelKeypadCode(uint8_t col, uint8_t row) {
    return ((col) << 4) | (1 << (row));
}

/** @brief Initialization of los-panel protocol

    Configures los-panel protocol class.
    @note https://mlf.home.xs4all.nl/los/ (defunct URL)
    @returns true
 */
bool LoSPanelProtocol::Init() {
    StampLastTx();
    m_LCDLastTxCommand = 0xFF;
    return true;
}

/** @brief Deinitialization of los-panel protocol class
 */
void LoSPanelProtocol::Exit() {
}

/** @brief Wait for given microseconds from last text LCD transfer
 */
void LoSPanelProtocol::WaitFromLastTx(
    uint32_t WaitMicros       /**< Time in microseconds to wait */
) {
    uint32_t WaitForMicros = m_LCDLastTxMicros + WaitMicros;

    if((WaitForMicros > m_LCDLastTxMicros) && (micros() >= WaitForMicros)) /* we are already over the target time */
        return;

//    digitalWrite(LED_BUILTIN, HIGH);

    if(WaitForMicros < m_LCDLastTxMicros) { /* we have an micros() overflow */
        while(micros() > m_LCDLastTxMicros) /* first run over the maximum */
            Yield();
    }

    while(micros() < WaitForMicros) /* now wait for target time */
        Yield();

//    digitalWrite(LED_BUILTIN, LOW);
}

/** @brief Store last LCD transfer time stamp
 */
void LoSPanelProtocol::StampLastTx() {
    m_LCDLastTxMicros = micros();
}

/** @brief Main loop of los-panel protocol

    This function reads UART if new data available and interpret the input based on los-panel protocol rules.
 */
void LoSPanelProtocol::Loop() {
    uint8_t RxByte;
    uint8_t SecondRxByte;

    if(m_UART->Available() == 0)
        return; /* Exit without waiting if there no UART data available */

    RxByte = m_UART->GetCh();
    switch(RxByte) {

    case LoSPanelProtocolInstruction:
        SecondRxByte = m_UART->GetCh();
        WaitFromLastTx(m_LCDLastTxCommand < 0x04? LosPanelProtocolLCDLongDelay: LosPanelProtocolLCDShortDelay); /* for commands 1 - 3 wait for 2 ms, otherwise 40 us */
        m_TextLCD->Command(SecondRxByte);
        m_LCDLastTxCommand = SecondRxByte;
        StampLastTx();
        break;

    case LoSPanelProtocolBacklight:
        SecondRxByte = m_UART->GetCh();
        m_TextLCD->SetBacklight(SecondRxByte);
        break;

    default:
        WaitFromLastTx(40);
        m_TextLCD->Write(RxByte);
        m_LCDLastTxCommand = 0xFF;
        StampLastTx();
        break;
    }
}

/** @brief Background job of los-panel protocol

    This function reads keyboard input and puts it to UART.
 */
void LoSPanelProtocol::Yield() {
    static uint8_t OldKey = KeyNone;
    uint8_t key = m_Keyboard->GetKey();

    if(OldKey != key)
        OldKey = key;
    else
        return;

    if(key != KeyNone) {
        uint8_t TxByte = LoSPanelKeypadCode(key >> 2, key & 0x3);
        m_UART->PutCh(LoSPanelProtocolKeypad);
        m_UART->PutCh(TxByte);
    }

    m_UART->Prefill();
}
