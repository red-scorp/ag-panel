/*!
  \file lcd.h
  \brief AG-Panel Project LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef LCD_H
#define LCD_H

#include "../../config.h"

/* Common LCD functions */
void lcd_init();
void lcd_welcome();
void lcd_write(uint8_t txbyte);
void lcd_command(uint8_t txbyte);

/* Specific LCD functions */
void lcd_init_display();
void lcd_init_backlight();
void lcd_set_backlight(uint8_t brightness);
void lcd_write_display(uint8_t txbyte);
void lcd_command_display(uint8_t txbyte);
void lcd_clear_display();
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print_string(const char *str);

/* New LCD functions for Hitachi HD44780 LCD emulation */
void lcd_clear();
//void lcd_home(); -> lcd_set_cursor
void lcd_set_cursor(uint8_t x, uint8_t y);
//void lcd_display(uint8_t on); -> part of protocol emulator
//void lcd_cursor(uint8_t on); -> not supported
//void lcd_blink(uint8_t on); -> not supported
//void lcd_scroll(uint8_t right); -> part of protocol emulator
//void lcd_direction(uint8_t left2right); -> part of protocol emulator
//void lcd_autoscroll(uint8_t on); -> part of protocol emulator
void lcd_create_char(uint8_t pos, uint8_t *buf); // to be defined!

#endif//LCD_H
