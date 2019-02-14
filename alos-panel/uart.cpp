/*!
  \file uart.cpp
  \brief ALoS-Panel Project UART code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "uart.h"

#include <HardwareSerial.cpp>

/* TODO: add Software UART too, instead of Hardware UART? */

/* UARD Configuration sanity check */
#if (!defined(UART_DIRECT) && !defined(UART_BUFFERED)) \
  || (defined(UART_DIRECT) && defined(UART_BUFFERED))
#error You should define UART_DIRECT or UART_BUFFERED and only one of them!
#endif

#if defined(UART_BUFFERED) && !defined(UART_BUF_SIZE)
#error You should define UART_BUF_SIZE for UART_BUFFERED UART type!
#endif

#if !defined(UART_BAUD)
#define UART_BAUD           9600
#endif

void uart_init() {
  Serial.begin(UART_BAUD);
}

uint8_t uart_putch(uint8_t txbyte) {
  return Serial.write(txbyte);
}

#if defined(UART_DIRECT)

uint8_t uart_getch() {

  while(Serial.available() == 0) {
  }

  return Serial.read();
}

#elif defined(UART_BUFFERED)

#if UART_BUF_SIZE <= 255
typedef uint8_t uart_buf_type;
#elif UART_BUF_SIZE <= 65535
typedef uint16_t uart_buf_type;
#else
typedef uint32_t uart_buf_type;
#endif//UART_BUF_SIZE

static uint8_t uart_buf[UART_BUF_SIZE] = {0};
static uart_buf_type uart_buf_filled = 0;

static uint8_t uart_fill_buffer() {

  while(uart_buf_filled < UART_BUF_SIZE && Serial.available() != 0) {
    uint8_t rxbyte = Serial.read();
    uart_buf[uart_buf_filled++] = rxbyte;
  }

  return uart_buf_filled;
}

static uint8_t uart_push_buffer() {

  uint8_t top_byte = uart_buf[0];

  for(uart_buf_type i = 1; i < uart_buf_filled; i++) {
    uart_buf[i - 1] = uart_buf[i];
  }

  uart_buf_filled--;
  return top_byte;
}

uint8_t uart_getch() {

  while(uart_fill_buffer() == 0) {
  }

  return uart_push_buffer();
}

#endif//UART_DIRECT
