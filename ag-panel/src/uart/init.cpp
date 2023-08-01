/** @file init.cpp
    @brief AG-Panel Project UART initialization
    @copyright (C) 2020-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#include "../private.h"
#include "../../config.h"

#include "all.h"

/** @brief Initialize communication interface

    This function chooses one of UART classes to use based on configuration defined in config.h
    @returns Pointer to communication UART class
 */
AbstractUART *initUART() {
    AbstractUART *p_UART = nullptr;

    /* Initialize communication UART class */
    #if defined(UART_HARDWARE)
        p_UART = new HardwareUART(UART_BAUD);
    #elif defined(UART_HARDWARE1)
        p_UART = new HardwareUART(UART_BAUD, 1);
    #elif defined(UART_HARDWARE2)
        p_UART = new HardwareUART(UART_BAUD, 2);
    #elif defined(UART_HARDWARE3)
        p_UART = new HardwareUART(UART_BAUD, 3);
    #elif defined(UART_HARDWARE4)
        p_UART = new HardwareUART(UART_BAUD, 4);
    #elif defined(UART_HARDWARE5)
        p_UART = new HardwareUART(UART_BAUD, 5);
    #elif defined(UART_HARDWARE6)
        p_UART = new HardwareUART(UART_BAUD, 6);
    #elif defined(UART_HARDWARE7)
        p_UART = new HardwareUART(UART_BAUD, 7);
    #elif defined(UART_HARDWARE8)
        p_UART = new HardwareUART(UART_BAUD, 8);
    #elif defined(UART_HARDWARE9)
        p_UART = new HardwareUART(UART_BAUD, 9);
    #elif defined(UART_HARDWARE10)
        p_UART = new HardwareUART(UART_BAUD, 10);
    #elif defined(UART_HARDWAREUSB)
        p_UART = new USBVirtualUART(UART_BAUD);
    #elif defined(UART_SOFTWARE)
        p_UART = new SoftwareUART(UART_BAUD, UART_PIN_RX, UART_PIN_TX);
    #elif defined(UART_NONE)
        p_UART = new NoneUART(UART_BAUD);
    #elif defined(UART_UT)
        /*p_UART = new UTUART();*/
    #else
        #error UART is not defined!
    #endif

    /* Enable UART extra buffering after main UART is initialized */
    #if defined(UART_BUFFERED)
        p_UART = new BufferedUART(p_UART, UART_BUF_SIZE);
    #endif

    /* Now we inject UART debugging layer to be able to spy after UART data */
    #if defined(DEBUG_UART_STR)
        p_UART = new TextLoggingUART(p_UART, g_DebugUART);
    #endif

    return p_UART;
}
