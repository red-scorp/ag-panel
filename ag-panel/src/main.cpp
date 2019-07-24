/*!
  \file main.cpp
  \brief AG-Panel Project main code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "../config.h"
#include "prot/prot.h"
#include "uart/uart.h"
#include "lcd/lcd.h"
#include "kbd/kbd.h"
#include "debug.h"

/*! \brief Main initialization function
 * - setup debugging
 * - setup UART
 * - setup LCD
 * - setup keyboard
 * - setup protocol
 */
void setup() {

  debug_init();

  uart_init();
  lcd_init();
  lcd_welcome();
  kbd_init();

  prot_init();
}

/*! \brief Main loop function
 * - run protocol
 * - start background task
 */
void loop() {

  prot_loop();
  prot_yield();
}

/*! \brief Background task function */
void yield() {

  prot_yield();
}
