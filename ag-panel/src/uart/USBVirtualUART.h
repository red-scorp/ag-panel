/** @file USBVirtualUART.h
    @brief AG-Panel Project direct USB virtual UART interface
    @copyright (C) 2020-2025 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "TemplateUART.h"

#if defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_STM32)

#if defined(ARDUINO_ARCH_SAMD)
    #if defined(ADAFRUIT_GRAND_CENTRAL_M4) || defined(ADAFRUIT_METRO_M4_EXPRESS)
        #include <USB/USBAPI.h>
        #define SerialUSB Serial /* this is a hack but it's ok for now */
    #else
        #include <USB/CDC.h>
    #endif
#endif

/** @brief USB virtual UART class

    This is a class which implements USB virtual UART of arduino boards.
    This class works with SAM, SAMD and STM32 MCUs only (for now).
 */
class USBVirtualUART: public TemplateUART<decltype(SerialUSB)> {

public:
    explicit USBVirtualUART(
        uint32_t BaudRate = DefaultUARTBaudRate   /**< Baud rate of an UART */
    ): TemplateUART(&SerialUSB, BaudRate) {
        Init();
    }
    virtual ~USBVirtualUART() override {
        Exit();
    }

    // virtual uint8_t PutCh(uint8_t TxByte) override;
    // virtual uint8_t GetCh() override;
    // virtual uint32_t Available() override;

protected:

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

#else
#warning 'USBVirtualUART' is not implemented for your platform. Use 'HardwareUART' or 'NoneUART' instead!
#endif //SAMD || SAM || STM32
