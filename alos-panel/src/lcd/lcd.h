/*!
  \file lcd.h
  \brief ALoS-Panel Project LCD interface
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

#endif//LCD_H
