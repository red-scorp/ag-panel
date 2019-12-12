/*!
  \file prot_rawserial.cpp
  \brief AG-Panel Project rawserial protocol code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "prot.h"
#include "../uart/uart.h"
#include "../lcd/lcd.h"
#include "../keyboard/kbd.h"

#if 0 //defined(PROT_RAWSERIAL)

/* Protocol commands definition */
/* TODO! */

/*! \brief Protocol main initialization function */
void prot_init() {
  /* TODO! */
}

/*! \brief Protocol main loop function
 * - read UART
 * - parse UART data and transfer it to LCD
 */
void prot_loop() {
  /* TODO! */
}

/*! \brief Protocol background task function
 * - read keyboard
 * - remove key repetitions
 * - send key over UART
 */
 void prot_yield() {
   /* TODO! */
}

#endif//PROT_RAWSERIAL
