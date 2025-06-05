/** @file HardwareUART.h
    @brief AG-Panel Project direct hardware UART interface
    @copyright (C) 2019-2025 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"
#include "TemplateUART.h"

/** @brief Hardware UART0 class

    This class implements hardware UART for port 0.
 */
class HardwareUART0 : public TemplateUART<decltype(Serial)> {
public:
    explicit HardwareUART0(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial, BaudRate) {}
};

#if defined(HAVE_HWSERIAL1) || defined(SERIAL_PORT_HARDWARE1) || SOC_UART_NUM > 1 || defined(__SERIAL1_DEVICE)
/** @brief Hardware UART1 class

    This class implements hardware UART for port 1.
 */
class HardwareUART1 : public TemplateUART<decltype(Serial1)> {
public:
    explicit HardwareUART1(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial1, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL2) || defined(SERIAL_PORT_HARDWARE2) || SOC_UART_NUM > 2 || defined(__SERIAL2_DEVICE)
/** @brief Hardware UART2 class

    This class implements hardware UART for port 2.
 */
class HardwareUART2 : public TemplateUART<decltype(Serial2)> {
public:
    explicit HardwareUART2(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial2, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL3) || defined(SERIAL_PORT_HARDWARE3) || SOC_UART_NUM > 3 || defined(__SERIAL3_DEVICE)
/** @brief Hardware UART3 class

    This class implements hardware UART for port 3.
 */
class HardwareUART3 : public TemplateUART<decltype(Serial3)> {
public:
    explicit HardwareUART3(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial3, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL4) || defined(SERIAL_PORT_HARDWARE4) || SOC_UART_NUM > 4 || defined(__SERIAL4_DEVICE)
/** @brief Hardware UART4 class

    This class implements hardware UART for port 4.
 */
class HardwareUART4 : public TemplateUART<decltype(Serial4)> {
public:
    explicit HardwareUART4(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial4, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL5) || defined(SERIAL_PORT_HARDWARE5) || SOC_UART_NUM > 5 || defined(__SERIAL5_DEVICE)
/** @brief Hardware UART5 class

    This class implements hardware UART for port 5.
 */
class HardwareUART5 : public TemplateUART<decltype(Serial5)> {
public:
    explicit HardwareUART5(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial5, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL6) || defined(SERIAL_PORT_HARDWARE6) || SOC_UART_NUM > 6 || defined(__SERIAL6_DEVICE)
/** @brief Hardware UART6 class

    This class implements hardware UART for port 6.
 */
class HardwareUART6 : public TemplateUART<decltype(Serial6)> {
public:
    explicit HardwareUART6(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial6, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL7) || defined(SERIAL_PORT_HARDWARE7) || SOC_UART_NUM > 7 || defined(__SERIAL7_DEVICE)
/** @brief Hardware UART7 class

    This class implements hardware UART for port 7.
 */
class HardwareUART7 : public TemplateUART<decltype(Serial7)> {
public:
    explicit HardwareUART7(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial7, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL8) || defined(SERIAL_PORT_HARDWARE8) || SOC_UART_NUM > 8 || defined(__SERIAL8_DEVICE)
/** @brief Hardware UART8 class

    This class implements hardware UART for port 8.
 */
class HardwareUART8 : public TemplateUART<decltype(Serial8)> {
public:
    explicit HardwareUART8(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial8, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL9) || defined(SERIAL_PORT_HARDWARE9) || SOC_UART_NUM > 9 || defined(__SERIAL9_DEVICE)
/** @brief Hardware UART9 class

    This class implements hardware UART for port 9.
 */
class HardwareUART9 : public TemplateUART<decltype(Serial9)> {
public:
    explicit HardwareUART9(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial9, BaudRate) {}
};
#endif

#if defined(HAVE_HWSERIAL10) || defined(SERIAL_PORT_HARDWARE10) || SOC_UART_NUM > 10 || defined(__SERIAL10_DEVICE)
/** @brief Hardware UART10 class

    This class implements hardware UART for port 10.
 */
class HardwareUART10 : public TemplateUART<decltype(Serial10)> {
public:
    explicit HardwareUART10(
        uint32_t BaudRate = DefaultUARTBaudRate /**< Baud rate of an UART */
    ) : TemplateUART(&Serial10, BaudRate) {}
};
#endif
