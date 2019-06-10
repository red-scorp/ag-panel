/*!
  \file uart.cpp
  \brief ALoS-Panel Project UART code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "uart.h"

/* TODO: add Software UART too, as alternative to Hardware UART? */

/* UART Configuration sanity check */
#if (!defined(UART_DIRECT) && !defined(UART_BUFFERED)) \
  || (defined(UART_DIRECT) && defined(UART_BUFFERED))
#error You should define UART_DIRECT or UART_BUFFERED and only one of them!
#endif
