/*!
  \file uart.h
  \brief AG-Panel Project UART interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef UART_H
#define UART_H

#include "../../config.h"
#include "../debug.h"

#if !defined(UART_BAUD)
#define UART_BAUD           9600
#endif

void uart_init();
uint8_t uart_putch(uint8_t txbyte);
uint8_t uart_getch();
void uart_prefill();

#if defined(DEBUG_UART_OUTPUT_HEX_STR)
uint8_t uart_putch_debug(uint8_t txbyte);
#define uart_putch(txbyte)  uart_putch_debug(txbyte)
#endif

#if defined(DEBUG_UART_INPUT_HEX_STR)
uint8_t uart_getch_debug();
#define uart_getch()        uart_getch_debug()
#endif

#endif//UART_H
