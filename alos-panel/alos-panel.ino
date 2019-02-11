/*!
  \file uart.cpp
  \brief ALoS-Panel Project main code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "config.h"
#include "uart.h"
#include "lcd.h"

#define LOS_INSTRUCTION     0xFE
#define LOS_KEYPAD          0xFE
#define LOS_BACKLIGHT       0xFD

#define LOS_BACKLIGHT_INIT  0x20
#define LOS_BACKLIGHT_OFF   0x00
#define LOS_BACKLIGHT_ON    0xFF

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

  // TODO: add check of keyboard pins and send data to uart
}
