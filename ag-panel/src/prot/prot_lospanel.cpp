/*!
  \file prot_lospanel.cpp
  \brief AG-Panel Project los-panel protocol code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "prot.h"
#include "../uart/uart.h"
#include "../lcd/lcd.h"
#include "../kbd/kbd.h"

#if defined(PROT_LOSPANAEL)

/* Protocol commands definition */
#define LOS_INSTRUCTION     0xFE
#define LOS_KEYPAD          0xFE
#define LOS_BACKLIGHT       0xFD

#define LOS_BACKLIGHT_OFF   0x00
#define LOS_BACKLIGHT_ON    0xFF

/*! \brief Protocol main initialization function */
void prot_init() {
  /* No initialization required */
}

/*! \brief Protocol main loop function
 * - read UART
 * - parse UART data and transfer it to LCD
 */
void prot_loop() {

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

}

/*! \brief Protocol background task function
 * - read keyboard
 * - remove key repetitions
 * - send key over UART
 */
 void prot_yield() {

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

#endif//PROT_LOSPANAEL
