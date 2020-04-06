/*!
  \file debug.h
  \brief AG-Panel Project debugging header
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

/* Drop UART input and output data to debug port as hex string */
//#define DEBUG_UART_STR

/* Enable DEBUG_STR() macro for basic UART text logging */
//#define DEBUG_STR_ENABLED

//#define DEBUG_UART_HARDWARE
//#define DEBUG_UART_HARDWARE1
//#define DEBUG_UART_HARDWARE2
//#define DEBUG_UART_HARDWARE3
//#define DEBUG_UART_HARDWAREUSB
//#define DEBUG_UART_SOFTWARE
#define DEBUG_UART_NONE

#define DEBUG_BAUD      115200

#if defined(DEBUG_UART_SOFTWARE)
#define DEBUG_PIN_RX    12
#define DEBUG_PIN_TX    13
#endif

#if defined(DEBUG_STR_ENABLED)
#include "uart/AbstractUART.h"
extern AbstractUART *g_DebugUART;
#define DEBUG_STR(str) g_DebugUART->PutStr(str)
#else
#define DEBUG_STR(str) /* Nothig */
#endif
