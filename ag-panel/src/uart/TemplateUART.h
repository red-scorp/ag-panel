/** @file TemplateUART.h
    @brief AG-Panel Project common UART template interface
    @copyright (C) 2025 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"
#include "Arduino.h"

/** @brief Template class for common UART

    This template class implements common UART for a specific port.
    It's designed to be used as a base for specific UART port classes.
 */
template<typename T>
class TemplateUART : public AbstractUART {
public:
    /** @brief Constructor for TemplateUART

        This constructor initializes the UART with a specific serial port and baud rate.
     */
    explicit TemplateUART(
        T* serialPort,          /**< Pointer to the Serial port object */
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : AbstractUART(BaudRate), m_UART(serialPort) {
        Init();
    }

    /** @brief Destructor for TemplateUART

        This destructor calls Exit() to clean up resources.
     */
    virtual ~TemplateUART() override {
        Exit();
    }

    /** @brief Write a character to UART

        This function writes a character to the UART.
        @returns Number of bytes written to UART
     */
    virtual uint8_t PutCh(
        uint8_t TxByte      /**< Character to be written to UART */
    ) override {
        return m_UART->write(TxByte);
    }

    /** @brief Read a character from UART

        This function reads a character from the UART.
        It blocks until a character is available.
        @returns Character (byte) read from UART
     */
    virtual uint8_t GetCh() override {
        while(Available() == 0) {
            yield();
        }
        return m_UART->read();
    }

    /** @brief Get the baud rate of the UART

        This function returns the baud rate of the UART.
        @returns Baud rate of the UART
     */
    virtual uint32_t Available() override {
        return m_UART->available();
    }

protected:    
    T* m_UART;               /**< Pointer to the Serial port object */

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
        m_UART = nullptr; // Set the UART pointer to nullptr to avoid dangling pointer
    }
};
