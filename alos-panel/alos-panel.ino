/*!
  \file uart.cpp
  \brief ALoS-Panel Project main code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "config.h"
#include "los.h"
#include "uart.h"
#include "lcd.h"
#include "kbd.h"

void setup() { 

  pinMode(LED_BUILTIN, OUTPUT);
  uart_init();

  digitalWrite(LED_BUILTIN, HIGH);

  lcd_init();
  lcd_welcome();

  digitalWrite(LED_BUILTIN, LOW);
}

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

  uint8_t key = kbd_getkey();

  if(key != KBD_KEY_NONE) {
    uart_putch(LOS_KEYPAD);
    uart_putch(key);
  }
}
