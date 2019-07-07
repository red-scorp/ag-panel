/*!
  \file los.cpp
  \brief AG-Panel Project main code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "../config.h"
#include "los.h"
#include "uart/uart.h"
#include "lcd/lcd.h"
#include "kbd/kbd.h"
#include "debug.h"

/*! \brief Main initialization function
 * - setup debugging
 * - setup UART
 * - setup LCD
 * - setup keyboard
 */
void setup() {

  debug_init();

  uart_init();
  lcd_init();
  lcd_welcome();
  kbd_init();
}

/*! \brief Main loop function
 * - read UART
 * - parse UART data and transfer it to LCD
 * - start background task
 */
void loop() {

  uint8_t rxbyte = uart_getch();

  switch(rxbyte) {

  case LOS_INSTRUCTION:
    lcd_command(uart_getch());
    break;

  case LOS_BACKLIGHT:
    lcd_set_backlight(uart_getch());
    break;

  default:
    lcd_write(rxbyte);
    break;
  }

  los_yield();
}

/*! \brief Background task function
 * - read keyboard
 * - remove key repetitions
 * - send key over UART
 */
void los_yield() {

  static uint8_t old_key = KBD_KEY_NONE;
  uint8_t key = kbd_getkey();

  if(old_key != key)
    old_key = key;
  else
    return;

  if(key != KBD_KEY_NONE) {
    uart_putch(LOS_KEYPAD);
    uart_putch(key);
  }

  uart_prefill();
}
