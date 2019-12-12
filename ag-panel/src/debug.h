/*!
  \file debug.h
  \brief AG-Panel Project debugging header
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef DEBUG_H
#define DEBUG_H

/* Drop UART input and output data to debug port as hex string */
//#define DEBUG_UART_STR

//#define DEBUG_UART_HARDWARE
//#define DEBUG_UART_HARDWARE1
//#define DEBUG_UART_HARDWARE2
//#define DEBUG_UART_HARDWARE3
#define DEBUG_UART_SOFTWARE

#define DEBUG_BAUD      115200

#if defined(DEBUG_UART_SOFTWARE)
#define DEBUG_PIN_RX    12
#define DEBUG_PIN_TX    13
#endif

#endif//DEBUG_H
