/*!
  \file lcd_i2c.cpp
  \brief ALoS-Panel Project I2C LCD code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
  \note https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
*/

#include "../private.h"
#include "lcd.h"

#if defined(LCD_I2C)

#if !defined(LCD_I2C_ADDR)
#error You should define LCD_I2C_ADDR for LCD_I2C!
#endif

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS);

/*! \brief Initialization of LCD display itself
 */
void lcd_init_display() {
  lcd.init();
}

/*! \brief Initialization of LCD display backlight LED
 */
void lcd_init_backlight() {
  lcd.backlight();
}

/*! \brief Set brightness of LCD display backlight LED
 */
void lcd_set_backlight(uint8_t brightness) {
  if(brightness == 0)
    lcd.noBacklight();
  else
    lcd.backlight();
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

#endif//LCD_I2C
