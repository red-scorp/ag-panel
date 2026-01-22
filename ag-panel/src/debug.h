/** @file debug.h
    @brief AG-Panel Project debugging header
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "uart/all.h"

/* Drop UART input and output data to debug port as hex string */
//#define DEBUG_UART_STR

/* Enable DEBUG_STR() macro for basic UART text logging */
//#define DEBUG_STR_ENABLED

//#define DEBUG_UART_HARDWARE
//#define DEBUG_UART_HARDWARE1
//#define DEBUG_UART_HARDWARE2
//#define DEBUG_UART_HARDWARE3
//#define DEBUG_UART_HARDWARE4
//#define DEBUG_UART_HARDWARE5
//#define DEBUG_UART_HARDWARE6
//#define DEBUG_UART_HARDWARE7
//#define DEBUG_UART_HARDWARE8
//#define DEBUG_UART_HARDWARE9
//#define DEBUG_UART_HARDWARE10
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
    #define DEBUG_STR(str) g_DebugUART->PutStr(str) /**< Print the string to debug UART */
#else
    #define DEBUG_STR(str) /* Nothing */
#endif

#define DEBUG_STR2(str1, str2)  {DEBUG_STR(str1); DEBUG_STR(str2);} /**< Print two strings to debug UART */
#define DEBUG_STR3(str1, str2, str3)  {DEBUG_STR(str1); DEBUG_STR(str2); DEBUG_STR(str3);}  /**< Print three strings to debug UART */
#define DEBUG_STR4(str1, str2, str3, str4)  {DEBUG_STR(str1); DEBUG_STR(str2); DEBUG_STR(str3); DEBUG_STR(str4)};   /**< Print four strings to debug UART */
#define DEBUG_STR5(str1, str2, str3, str4, str5)  {DEBUG_STR(str1); DEBUG_STR(str2); DEBUG_STR(str3); DEBUG_STR(str4); DEBUG_STR(str5);}    /**< Print five strings to debug UART */

extern AbstractUART* initDebug();
