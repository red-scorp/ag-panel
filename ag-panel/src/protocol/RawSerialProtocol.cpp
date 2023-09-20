/** @file RawSerialProtocol.cpp
    @brief AG-Panel Project raw serial protocol implementation
    @copyright (C) 2020-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "RawSerialProtocol.h"

/* Protocol commands definition */
const uint8_t RawSerialProtocolEndOfBuffer = '\n';    /**< End of buffer command, comes from host to target */

/** @brief Initialization of rawserial protocol

    Configures rawserial protocol class.
    @returns true
 */
bool RawSerialProtocol::Init() {
    return true;
}

/** @brief Deinitialization of rawserial protocol class
 */
void RawSerialProtocol::Exit() {
}

/** @brief Main loop of rawserial protocol

    This function reads UART if new data available and interpret the input based on rawserial protocol rules.
 */
void RawSerialProtocol::Loop() {
    uint8_t RxByte;

    if(m_UART->Available() == 0)
        return; /* Exit without waiting if there no UART data available */

    RxByte = m_UART->GetCh();

    if(!m_ShowRealData) { /* first real data received -> clear screen and reset output coordinates */
        m_XPos = 0;
        m_YPos = 0;
        m_LCD->Clear();
        m_LCD->SetCursor(m_XPos, m_YPos);
        m_ShowRealData = true;
    }

    if(RxByte == RawSerialProtocolEndOfBuffer) { /* end of buffer command -> go to beginning of a screen */
        m_XPos = 0;
        m_YPos = 0;
        m_OutOfRange = false;
        m_LCD->SetCursor(m_XPos, m_YPos);
    } else {
        if(m_XPos >= m_LCD->GetColumns()) { /* end of line condition -> go to new line */
            m_XPos = 0;
            m_YPos++;
            if(m_YPos >= m_LCD->GetRows()) /* end of buffer reached -> print nothing until proper command is received */
                m_OutOfRange = true;
            if(!m_OutOfRange)
                m_LCD->SetCursor(m_XPos, m_YPos);
        }
        if(!m_OutOfRange) {
            char character = RxByte;
            m_LCD->Print(character);
            m_XPos++;
        }
    }
}

/** @brief Background job of rawserial protocol

    This function reads keyboard input and puts it to UART.
 */
void RawSerialProtocol::Yield() {
    static uint8_t OldKey = KeyNone;
    uint8_t key = m_Keyboard->GetKey();

    if(OldKey != key)
        OldKey = key;
    else
        return;

    if(key != KeyNone) {
        uint8_t TxByte = key;
        m_UART->PutCh(TxByte);
    }

    m_UART->Prefill();
}
