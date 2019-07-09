/*!
  \file uart.cpp
  \brief AG-Panel Project UART code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "uart.h"
#include "../debug.h"

/* TODO: add Software UART too, as alternative to Hardware UART? */

/* UART Configuration sanity check */
#if (!defined(UART_DIRECT) && !defined(UART_BUFFERED)) \
  || (defined(UART_DIRECT) && defined(UART_BUFFERED))
#error You should define UART_DIRECT or UART_BUFFERED and only one of them!
#endif

#if defined(DEBUG_UART_OUTPUT_HEX_STR) || defined(DEBUG_UART_INPUT_HEX_STR)
static const char hex_to_char[] = "01234567890ABCDEF";
static uint8_t direction = 2;
#endif

#if defined(DEBUG_UART_OUTPUT_HEX_STR)
#undef uart_putch
uint8_t uart_putch_debug(uint8_t txbyte) {
  uint8_t r;
  char hex_str[] = " xx";
  r = uart_putch(txbyte);
  if(direction != 0) {
    debug_puts("\n\r>");
    direction = 0;
  }
  hex_str[1] = hex_to_char[txbyte >> 4];
  hex_str[2] = hex_to_char[txbyte & 0xF];
  debug_puts(hex_str);
  return r;
}
#endif

#if defined(DEBUG_UART_INPUT_HEX_STR)
#undef uart_getch
uint8_t uart_getch_debug() {
  uint8_t r;
  char hex_str[] = " xx";
  r = uart_getch();
  if(direction != 1) {
    debug_puts("\n\r<");
    direction = 1;
  }
  hex_str[1] = hex_to_char[r >> 4];
  hex_str[2] = hex_to_char[r & 0xF];
  debug_puts(hex_str);
  return r;
}
#endif
