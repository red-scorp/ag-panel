/*!
  \file init.cpp
  \brief AG-Panel Project UART initialization
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"

#include "all.h"

/*!
  \brief Initialize communication interface

  This function chooses one of UART classes to use based on configuration defined in config.h
  \returns Pointer to communication UART class
 */
AbstractUART *initUART() {
  AbstractUART *UART = nullptr;

  /* Initialize communication UART class */
  #if defined(UART_HARDWARE)
    UART = new HardwareUART(UART_BAUD);
  #elif defined(UART_HARDWARE1)
    UART = new HardwareUART(UART_BAUD, 1);
  #elif defined(UART_HARDWARE2)
    UART = new HardwareUART(UART_BAUD, 2);
  #elif defined(UART_HARDWARE3)
    UART = new HardwareUART(UART_BAUD, 3);
  #elif defined(UART_HARDWARE4)
    UART = new HardwareUART(UART_BAUD, 4);
  #elif defined(UART_HARDWARE5)
    UART = new HardwareUART(UART_BAUD, 5);
  #elif defined(UART_HARDWARE6)
    UART = new HardwareUART(UART_BAUD, 6);
  #elif defined(UART_HARDWARE7)
    UART = new HardwareUART(UART_BAUD, 7);
  #elif defined(UART_HARDWARE8)
    UART = new HardwareUART(UART_BAUD, 8);
  #elif defined(UART_HARDWARE9)
    UART = new HardwareUART(UART_BAUD, 9);
  #elif defined(UART_HARDWARE10)
    UART = new HardwareUART(UART_BAUD, 10);
  #elif defined(UART_HARDWAREUSB)
    UART = new USBVirtualUART(UART_BAUD);
  #elif defined(UART_SOFTWARE)
    UART = new SoftwareUART(UART_BAUD, UART_PIN_RX, UART_PIN_TX);
  #elif defined(UART_NONE)
    UART = new NoneUART(UART_BAUD);
  #else
    #error UART is not defined!
  #endif

  /* Enable UART extra buffering after main uart is initialized */
  #if defined(UART_BUFFERED)
    UART = new BufferedUART(UART, UART_BUF_SIZE);
  #endif

  /* Now we inject UART debugging layer to be able to spy after UART data */
  #if defined(DEBUG_UART_STR)
    UART = new TextLoggingUART(UART, g_DebugUART);
  #endif

  return UART;
}
