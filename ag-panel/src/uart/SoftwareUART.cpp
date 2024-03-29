/** @file SoftwareUART.cpp
    @brief AG-Panel Project direct software UART implementation
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "SoftwareUART.h"

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_ESP32) // || defined(ARDUINO_ARCH_ESP8266)
#include <SoftwareSerial.h>

/** @brief Initialization of software UART

    Initialize software UART and set baud rate.
    @returns true
 */
bool SoftwareUART::Init() {
    m_Lowlevel = new SoftwareSerial(m_RxPin, m_TxPin);
    SoftwareSerial *p_UART = reinterpret_cast<SoftwareSerial*>(m_Lowlevel);
    p_UART->begin(m_BaudRate);
    return true;
}

/** @brief Deinitialization of software UART
 */
void SoftwareUART::Exit() {
    SoftwareSerial *p_UART = reinterpret_cast<SoftwareSerial*>(m_Lowlevel);
    if(p_UART != nullptr)
        delete p_UART;
    m_Lowlevel = nullptr;
}

/** @brief Write a character to software UART

    @returns Number of bytes written to software UART
 */
uint8_t SoftwareUART::PutCh(
    uint8_t TxByte      /**< Character to be written to software UART */
) {
    SoftwareSerial *p_UART = reinterpret_cast<SoftwareSerial*>(m_Lowlevel);
    return p_UART->write(TxByte);
}

/** @brief Read a character from software UART

    @returns Character (byte) read from software UART
 */
uint8_t SoftwareUART::GetCh() {
    SoftwareSerial *p_UART = reinterpret_cast<SoftwareSerial*>(m_Lowlevel);
    while(Available() == 0) {
        yield();
    }

    return p_UART->read();
}

/** @brief Check number of bytes in software UART buffer

    @returns Number of bytes stored in buffer of software UART
 */
uint32_t SoftwareUART::Available() {
    SoftwareSerial *p_UART = reinterpret_cast<SoftwareSerial*>(m_Lowlevel);
    return p_UART->available();
}

#else
#warning 'SoftwareUART' is not implemented for your platform. Use 'HardwareUART' or 'NoneUART' instead!
#endif
