/*!
  \file lcd.h
  \brief ALoS-Panel Project LCD interface
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef LCD_H
#define LCD_H

#include "config.h"

void lcd_init();
void lcd_welcome();
void lcd_write(uint8_t txbyte);
void lcd_command(uint8_t txbyte);

void lcd_init_backlight();
void lcd_set_backlight(uint8_t brightness);

#endif//LCD_H
