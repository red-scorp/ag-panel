/** @file SoftwareUART.h
    @brief AG-Panel Project direct software UART interface
    @copyright (C) 2019-2025 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"
#include "TemplateUART.h"

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_RP2040)

#include "SoftwareSerial.h"

/** @brief Software UART class

    This is a class which implements software UART of arduino boards.
    This class works with AVR, ESP32 and STM32 MCUs only (for now).
 */
class SoftwareUART: public TemplateUART<SoftwareSerial> {

public:
    /** @brief Constructor for SoftwareUART

        This constructor initializes the software UART with a specific baud rate and TX/RX pins.
     */
    explicit SoftwareUART(
        uint32_t BaudRate,    /**< Baud rate of an UART */
        uint8_t RxPin,        /**< Receive data UART pin */
        uint8_t TxPin         /**< Transmit data UART pin */
    ): TemplateUART(new SoftwareSerial(RxPin, TxPin), BaudRate),
        m_RxPin(RxPin), m_TxPin(TxPin) {
            Init();
        }

    /** @brief Destructor for SoftwareUART

        This destructor calls Exit() to clean up resources.
     */
    virtual ~SoftwareUART() override {
        Exit();
    }

    virtual uint8_t PutCh(uint8_t TxByte) override;
    virtual uint8_t GetCh() override;
    virtual uint32_t Available() override;

protected:
    uint8_t m_RxPin;        /**< Receive data UART pin */
    uint8_t m_TxPin;        /**< Transmit data UART pin */

private:
    /** @brief Initialize the UART

        This function initializes the UART by starting the serial port with the specified baud rate.
        @returns true if initialization is successful
     */
    bool Init() {
        m_UART->begin(m_BaudRate);
        return true;
    }

    /** @brief Exit the UART

        This function cleans up resources used by the UART.
     */
    void Exit() {
        delete m_UART; // Clean up the SoftwareSerial object
    }
};

#endif
