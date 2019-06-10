/*!
  \file uart.cpp
  \brief ALoS-Panel Project UART code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "uart.h"

#include <HardwareSerial.cpp>

/* TODO: add Software UART too, instead of Hardware UART? */

/* UART Configuration sanity check */
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

/*! \brief Initialization of UART
 * - Set UART baud rate
 */
void uart_init() {
  Serial.begin(UART_BAUD);
}

/*! \brief Write byte to UART
 */
uint8_t uart_putch(uint8_t txbyte) {
  return Serial.write(txbyte);
}

#if defined(UART_DIRECT)

/*! \brief Read byte from UART
 * - Read UART if data available
 * - Start background task while waiting for data from UART
 */
uint8_t uart_getch() {

  while(Serial.available() == 0) {
    los_yield();
  }

  return Serial.read();
}

/*! \brief Prepare data in UART to be read
 */
void uart_prefill() {
  /* Does nothing for direct UART */
}

#elif defined(UART_BUFFERED)

#if UART_BUF_SIZE <= 255
typedef uint8_t uart_buf_type;
#elif UART_BUF_SIZE <= 65535
typedef uint16_t uart_buf_type;
#else
typedef uint32_t uart_buf_type;
#endif//UART_BUF_SIZE

/*! \brief UART buffer array */
static uint8_t uart_buf[UART_BUF_SIZE] = {0};
/*! \brief Counter of bytes stored in UART buffer */
static uart_buf_type uart_buf_filled = 0;

/*! \brief Fill UART buffer
 * - Read UART if data available
 * - Copy data UART data buffer
 */
static uint8_t uart_fill_buffer() {

  while(uart_buf_filled < UART_BUF_SIZE && Serial.available() != 0) {
    uint8_t rxbyte = Serial.read();
    uart_buf[uart_buf_filled++] = rxbyte;
  }

  return uart_buf_filled > 255? 255: uart_buf_filled;
}

/*! \brief Push data from UART buffer
 * - Get first byte from UART buffer
 * - Pull all stored bytes one step to the front
 * - Return stored earlier first byte
 */
static uint8_t uart_push_buffer() {

  uint8_t top_byte = uart_buf[0];

  for(uart_buf_type i = 1; i < uart_buf_filled; i++) {
    uart_buf[i - 1] = uart_buf[i];
  }

  uart_buf_filled--;
  return top_byte;
}

/*! \brief Read byte from UART buffer
 * - Fill UART buffer with data
 * - Start background task while waiting for data from UART
 * - Read byte from UART buffer
 */
uint8_t uart_getch() {

  while(uart_fill_buffer() == 0) {
    los_yield();
  }

  return uart_push_buffer();
}

/*! \brief Prepare data in UART to be read
 * - Fill UART data buffer
 */
void uart_prefill() {
  uart_fill_buffer();
}

#endif//UART_DIRECT
