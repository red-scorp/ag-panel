/*!
  \file lcd_i2c_rgb.cpp
  \brief AG-Panel Project I2C RGB LCD code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
  \note https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
*/

#include "../private.h"
#include "lcd.h"

#if defined(LCD_I2C_RGB)

#if!defined(LCD_BACKLIGHT_COLOR)
#error You should define LCD_BACKLIGHT_COLOR for LCD_I2C_RGB!
#endif

#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd;

/*! \brief Initialization of LCD display itself
 */
void lcd_init_display() {
  lcd.begin(LCD_ROWS, LCD_COLS);
}

/*! \brief Initialization of LCD display backlight LED
 */
void lcd_init_backlight() {
  lcd.setBacklight(LCD_BACKLIGHT_COLOR);
}

/*! \brief Set brightness of LCD display backlight LED
 */
void lcd_set_backlight(uint8_t brightness) {
  if(brightness == 0)
    lcd.setBacklight(0); /* does it work? */
  else
    lcd.setBacklight(LCD_BACKLIGHT_COLOR);
}

/*! \brief Write character to LCD display directly
 */
void lcd_write_display(uint8_t txbyte) {
  lcd.write(txbyte);
}

/*! \brief Send command to LCD display directly
 */
void lcd_command_display(uint8_t txbyte) {
  lcd.command(txbyte);
}

/*! \brief Clear LCD display
 */
void lcd_clear_display() {
  lcd.clear();
}

/*! \brief Set cursor to specific positon on LCD display
 */
void lcd_set_cursor(uint8_t row, uint8_t col) {
  lcd.setCursor(row, col);
}

/*! \brief Print a string on LCD display
 */
void lcd_print_string(const char *str) {
  lcd.print(str);
}

#endif//LCD_I2C_RGB
