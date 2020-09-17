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
  AbstractUART *p_DebugUART = nullptr;

  #if defined(DEBUG_UART_HARDWARE)
    p_DebugUART = new HardwareUART(DEBUG_BAUD);
  #elif defined(DEBUG_UART_HARDWARE1)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 1);
  #elif defined(DEBUG_UART_HARDWARE2)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 2);
  #elif defined(DEBUG_UART_HARDWARE3)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 3);
  #elif defined(DEBUG_UART_HARDWARE4)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 4);
  #elif defined(DEBUG_UART_HARDWARE5)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 5);
  #elif defined(DEBUG_UART_HARDWARE6)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 6);
  #elif defined(DEBUG_UART_HARDWARE7)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 7);
  #elif defined(DEBUG_UART_HARDWARE8)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 8);
  #elif defined(DEBUG_UART_HARDWARE9)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 9);
  #elif defined(DEBUG_UART_HARDWARE10)
    p_DebugUART = new HardwareUART(DEBUG_BAUD, 10);
  #elif defined(DEBUG_UART_HARDWAREUSB)
    p_DebugUART = new USBVirtualUART(DEBUG_BAUD);
  #elif defined(DEBUG_UART_SOFTWARE)
    p_DebugUART = new SoftwareUART(DEBUG_BAUD, DEBUG_PIN_RX, DEBUG_PIN_TX);
  #elif defined(DEBUG_UART_NONE)
    p_DebugUART = new NoneUART(DEBUG_BAUD);
  #else
    #error Debug UART is not defined!
  #endif

  return p_DebugUART;
}
