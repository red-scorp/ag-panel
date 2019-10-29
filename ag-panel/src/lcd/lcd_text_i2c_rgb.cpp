/*!
  \file lcd_text_i2c_rgb.cpp
  \brief AG-Panel Project I2C RGB LCD code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
  \note https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
*/

#include "../private.h"
#include "lcd.h"

#if defined(LCD_TEXT_I2C_RGB)

#if !defined(LCD_BACKLIGHT_COLOR)
#error You should define LCD_BACKLIGHT_COLOR for LCD_TEXT_I2C_RGB!
#endif

#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield rgb_lcd;

/*! \brief Initialization of LCD display itself
 */
void lcd_init_display() {
  rgb_lcd.begin(LCD_ROWS, LCD_COLS);
}

/*! \brief Initialization of LCD display backlight LED
 */
void lcd_init_backlight() {
  rgb_lcd.setBacklight(LCD_BACKLIGHT_COLOR);
}

/*! \brief Set brightness of LCD display backlight LED
 */
void lcd_set_backlight(uint8_t brightness) {
  if(brightness == 0)
    rgb_lcd.setBacklight(0); /* does it work? */
  else
    rgb_lcd.setBacklight(LCD_BACKLIGHT_COLOR);
}

/*! \brief Write character to LCD display directly
 */
void lcd_write_display(uint8_t txbyte) {
  rgb_lcd.write(txbyte);
}

/*! \brief Send command to LCD display directly
 */
void lcd_command_display(uint8_t txbyte) {
  rgb_lcd.command(txbyte);
}

/*! \brief Clear LCD display
 */
void lcd_clear_display() {
  rgb_lcd.clear();
}

/*! \brief Set cursor to specific positon on LCD display
 */
void lcd_set_cursor(uint8_t row, uint8_t col) {
  rgb_lcd.setCursor(row, col);
}

/*! \brief Print a string on LCD display
 */
void lcd_print_string(const char *str) {
  rgb_lcd.print(str);
}

#endif//LCD_TEXT_I2C_RGB
