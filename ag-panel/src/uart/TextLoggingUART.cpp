/** @file TextLoggingUART.cpp
    @brief AG-Panel Project text logging UART implementation
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "TextLoggingUART.h"

const uint8_t NumbersLineBinary = 2;
const uint8_t NumbersLineOctal = 8;
const uint8_t NumbersLineDecimal = 10;
const uint8_t NumbersLineHexadecimal = 16;

static const char s_Numbers[] = "0123456789ABCDEF";

/** @brief Initialization of text logging UART

    Initialize text logging UART.
    @returns true
 */
bool TextLoggingUART::Init() {

    switch(m_NumbersBase) {
    case NumbersBaseBinary:
    case NumbersBaseOctal:
    case NumbersBaseDecimal:
    case NumbersBaseHexadecimal:
        /* Everything ok. do nothing */
        break;
    default:
        m_NumbersBase = DefaultNumbersBase;
        break;
    }

    switch(m_NumbersBase) {
    case NumbersBaseBinary:
        m_NumberLength = 8;
        m_WrapLineLength = NumbersLineBinary;
        m_LeadingZeros = 1;
        break;
    case NumbersBaseOctal:
        m_NumberLength = 3;
        m_WrapLineLength = NumbersLineOctal;
        m_LeadingZeros = 1;
        break;
    case NumbersBaseDecimal:
        m_NumberLength = 3;
        m_WrapLineLength = NumbersLineDecimal;
        m_LeadingZeros = 0;
        break;
    case NumbersBaseHexadecimal:
        m_NumberLength = 2;
        m_WrapLineLength = NumbersLineHexadecimal;
        m_LeadingZeros = 1;
        break;
    }

    return true;
}

/** @brief Deinitialization of text logging UART
 */
void TextLoggingUART::Exit() {
}

/** @brief Write a character to text logging UART

    @returns Number of bytes written to real UART
 */
uint8_t TextLoggingUART::PutCh(
    uint8_t txbyte      /**< Character to be written to text logging UART */
) {
    PrintByte(txbyte, 0);
    return m_RealUART->PutCh(txbyte);
}

/** @brief Read a character from text logging UART

    @returns Character (byte) read from real UART
 */
uint8_t TextLoggingUART::GetCh() {
    uint8_t rxbyte = m_RealUART->GetCh();
    PrintByte(rxbyte, 1);
    return rxbyte;
}

/** @brief Check number of bytes in text logging UART buffer

    @returns Number of bytes stored in buffer of real UART
 */
uint32_t TextLoggingUART::Available() {
    return m_RealUART->Available();
}

/** @brief Get baud rate of text logging UART

    @returns Baud rate of real UART
 */
uint32_t TextLoggingUART::GetBaudRate() const {
    return m_RealUART->GetBaudRate();
}

/** @brief Print a byte

    This function prints given byte in specified format to a debug UART.
 */
void TextLoggingUART::PrintByte(
    uint8_t byte,       /**< byte to be printed */
    uint8_t direction   /**< direction it goes to */
) {
    char str[m_NumberLength + 1];
    char *p;
    uint8_t meet_nonzero = 0;

    if(m_Direction != direction) {
        m_DebugUART->PutCh('\n');
        m_DebugUART->PutCh('\r');
        m_DebugUART->PutCh(direction == 0? '>': '<');
        m_Direction = direction;
    }

    p = &str[m_NumberLength];
    *p-- = '\0';
    for(uint8_t i = 0; i < m_NumberLength; i++) {
        uint8_t digit = byte % m_NumbersBase;
        byte = byte / m_NumbersBase;
        *p-- = s_Numbers[digit];
    }

    m_DebugUART->PutCh(' ');
    for(uint8_t i = 0; i < m_NumberLength; i++) {
        if(m_LeadingZeros) {
        m_DebugUART->PutCh(str[i]);
        } else {
        if(meet_nonzero || i == m_NumberLength - 1 || str[i] != '0') {
            m_DebugUART->PutCh(str[i]);
            meet_nonzero = 1;
        } else {
            m_DebugUART->PutCh(' ');
        }
        }
    }

    if(m_LineWrap) {
        m_CurrentLineLength++;
        if(m_CurrentLineLength >= m_WrapLineLength) {
            m_Direction = 2;
            m_CurrentLineLength = 0;
        }
    }
}
