/** @file SoftwareUART.cpp
    @brief AG-Panel Project direct software UART implementation
    @copyright (C) 2019-2025 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "SoftwareUART.h"

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_ESP32) // || defined(ARDUINO_ARCH_ESP8266)
#include <SoftwareSerial.h>

/** @brief Initialization of software UART
 *
 * Initialize software UART and set baud rate.
 * @returns true
 */
bool SoftwareUART::Init() {
    m_UART->begin(m_BaudRate);
    return true;
}

/** @brief Deinitialization of software UART
 */
void SoftwareUART::Exit() {
    // Nothing to do here, the SoftwareSerial object will be deleted by the template class
}

#else
#warning 'SoftwareUART' is not implemented for your platform. Use 'HardwareUART' or 'NoneUART' instead!
#endif
