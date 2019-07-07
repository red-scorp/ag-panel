/*!
  \file debug.h
  \brief AG-Panel Project debugging header
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef DEBUG_H
#define DEBUG_H

/* Drop UART output data to debug port as hex string */
//#define DEBUG_UART_OUTPUT_HEX_STR

/* Drop UART input data to debug port as hex string */
//#define DEBUG_UART_INPUT_HEX_STR

//#define DEBUG_HW_SERIAL
//#define DEBUG_HW_SERIAL1
//#define DEBUG_HW_SERIAL2
//#define DEBUG_HW_SERIAL3
//#define DEBUG_SW_SERIAL

#define DEBUG_BAUD      115200

#if defined(DEBUG_SW_SERIAL)
#define DEBUG_PIN_TX    13
#define DEBUG_PIN_RX    12
#endif

void debug_init();
void debug_putch(uint8_t txbyte);
void debug_puts(char *str);

#endif//DEBUG_H
