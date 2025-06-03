/** @file SoftwareUART.h
    @brief AG-Panel Project direct software UART interface
    @copyright (C) 2019-2025 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"
#include "TemplateUART.h"
#include "SoftwareSerial.h"

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_ESP32) // || defined(ARDUINO_ARCH_ESP8266)

/** @brief Software UART class

    This is a class which implements software UART of arduino boards.
    This class works with AVR, ESP32 and STM32 MCUs only (for now).
 */
class SoftwareUART: public TemplateUART<SoftwareSerial> {

public:
    explicit SoftwareUART(
        uint32_t BaudRate,    /**< Baud rate of an UART */
        uint8_t RxPin,        /**< Receive data UART pin */
        uint8_t TxPin         /**< Transmit data UART pin */
    ): TemplateUART(new SoftwareSerial(RxPin, TxPin), BaudRate),
        m_RxPin(RxPin),
        m_TxPin(TxPin) { Init(); }
    virtual ~SoftwareUART() override { Exit(); }

    virtual uint8_t PutCh(uint8_t TxByte) override;
    virtual uint8_t GetCh() override;
    virtual uint32_t Available() override;

protected:
    uint8_t m_RxPin;        /**< Receive data UART pin */
    uint8_t m_TxPin;        /**< Transmit data UART pin */

private:
    bool Init();
    void Exit();
};

#endif /* defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_ESP32) */