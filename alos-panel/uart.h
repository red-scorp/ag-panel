/*!
  \file uart.h
  \brief ALoS-Panel Project UART interface
*/

#ifndef UART_H
#define UART_H

#include "config.h"

void uart_init();
uint8_t uart_putch(uint8_t txbyte);
uint8_t uart_getch();

#endif//UART_H
