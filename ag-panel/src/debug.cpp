/*!
  \file debug.cpp
  \brief AG-Panel Project debugging helper functions
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "private.h"
#include "../config.h"

#include "debug.h"

/*!
  \brief Initialize debug interface

  This function chooses one of UART classes to use based on configuration defined in config.h
  \returns Pointer to debugging UART class
 */
AbstractUART* initDebug() {
  AbstractUART *debugUART = nullptr;

  #if defined(DEBUG_UART_HARDWARE)
    debugUART = new HardwareUART(DEBUG_BAUD);
  #elif defined(DEBUG_UART_HARDWARE1)
    debugUART = new HardwareUART(DEBUG_BAUD, 1);
  #elif defined(DEBUG_UART_HARDWARE2)
    debugUART = new HardwareUART(DEBUG_BAUD, 2);
  #elif defined(DEBUG_UART_HARDWARE3)
    debugUART = new HardwareUART(DEBUG_BAUD, 3);
  #elif defined(DEBUG_UART_HARDWARE4)
    debugUART = new HardwareUART(DEBUG_BAUD, 4);
  #elif defined(DEBUG_UART_HARDWARE5)
    debugUART = new HardwareUART(DEBUG_BAUD, 5);
  #elif defined(DEBUG_UART_HARDWARE6)
    debugUART = new HardwareUART(DEBUG_BAUD, 6);
  #elif defined(DEBUG_UART_HARDWARE7)
    debugUART = new HardwareUART(DEBUG_BAUD, 7);
  #elif defined(DEBUG_UART_HARDWARE8)
    debugUART = new HardwareUART(DEBUG_BAUD, 8);
  #elif defined(DEBUG_UART_HARDWARE9)
    debugUART = new HardwareUART(DEBUG_BAUD, 9);
  #elif defined(DEBUG_UART_HARDWARE10)
    debugUART = new HardwareUART(DEBUG_BAUD, 10);
  #elif defined(DEBUG_UART_HARDWAREUSB)
    debugUART = new USBVirtualUART(DEBUG_BAUD);
  #elif defined(DEBUG_UART_SOFTWARE)
    debugUART = new SoftwareUART(DEBUG_BAUD, DEBUG_PIN_RX, DEBUG_PIN_TX);
  #elif defined(DEBUG_UART_NONE)
    debugUART = new NoneUART(DEBUG_BAUD);
  #else
    #error Debug UART is not defined!
  #endif

  return debugUART;
}
