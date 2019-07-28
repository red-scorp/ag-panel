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

#if defined(PROT_LOSPANEL)

/* Protocol commands definition */
#define LOS_INSTRUCTION     0xFE
#define LOS_KEYPAD          0xFE
#define LOS_BACKLIGHT       0xFD

#define LOS_BACKLIGHT_OFF   0x00
#define LOS_BACKLIGHT_ON    0xFF

/*! \brief Last LCD transfer microseconds time stamp value
 */
static uint32_t lcd_last_tx_micros = 0;

/*! \brief Wait for given microseconds from last LCD transfer
 */
static void wait_from_last_tx(uint32_t wait_micros) {
  uint32_t wait_for_micros = lcd_last_tx_micros + wait_micros;

  if((wait_for_micros > lcd_last_tx_micros) && (micros() >= wait_for_micros)) /* we are already over the target time */
    return;

//  digitalWrite(LED_BUILTIN, HIGH);

  if(wait_for_micros < lcd_last_tx_micros) { /* we have an micros() overflow */
    while(micros() > lcd_last_tx_micros) /* first run over the maximum */
      prot_yield();
  }

  while(micros() < wait_for_micros) /* now wait for target time */
    prot_yield();

//  digitalWrite(LED_BUILTIN, LOW);
}

/*! \brief Store last LCD transfer time stamp
 */
static void stamp_last_tx() {
  lcd_last_tx_micros = micros();
}

/*! \brief Write character to LCD display
 */
static void prot_lcd_write(uint8_t txbyte) {
  wait_from_last_tx(40);
  lcd_write_display(txbyte);
  stamp_last_tx();
}

/*! \brief Send command to LCD display
 */
static void prot_lcd_command(uint8_t txbyte) {
  wait_from_last_tx(txbyte < 4? 2000: 40); /* for commands 1 - 3 wait for 2 ms, otherwise 40 us */
  lcd_command_display(txbyte);
  stamp_last_tx();
}

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
    prot_lcd_command(uart_getch());
    break;

  case LOS_BACKLIGHT:
    lcd_set_backlight(uart_getch());
    break;

  default:
    prot_lcd_write(rxbyte);
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

#endif//PROT_LOSPANEL
