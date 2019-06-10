/*!
  \file uart.h
  \brief ALoS-Panel Project UART interface
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef UART_H
#define UART_H

#include "../../config.h"

#if !defined(UART_BAUD)
#define UART_BAUD           9600
#endif

void uart_init();
uint8_t uart_putch(uint8_t txbyte);
uint8_t uart_getch();
void uart_prefill();

#endif//UART_H
