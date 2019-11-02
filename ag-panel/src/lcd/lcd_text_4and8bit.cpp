/*!
  \file lcd_tetx_4and8bit.cpp
  \brief AG-Panel Project 4- and 8-bit LCD code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
  \note https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
*/

#include "../private.h"
#include "lcd.h"

#if defined(LCD_TEXT_4BIT) || defined(LCD_TEXT_8BIT)

#if (!defined(LCD_BACKLIGHT_NONE) && !defined(LCD_BACKLIGHT_ONOFF) && !defined(LCD_BACKLIGHT_PWM)) \
  || (defined(LCD_BACKLIGHT_NONE) && defined(LCD_BACKLIGHT_ONOFF)) \
  || (defined(LCD_BACKLIGHT_NONE) && defined(LCD_BACKLIGHT_PWM)) \
  || (defined(LCD_BACKLIGHT_ONOFF) && defined(LCD_BACKLIGHT_PWM))
#error You should define LCD_BACKLIGHT_NONE, LCD_BACKLIGHT_ONOFF or LCD_BACKLIGHT_PWM and only one of them!
#endif

#if defined(LCD_TEXT_4BIT) && \
  (!defined(LCD_PIN_RS) || !defined(LCD_PIN_ENABLE) \
  || !defined(LCD_PIN_D4) || !defined(LCD_PIN_D5) \
  || !defined(LCD_PIN_D6) || !defined(LCD_PIN_D7))
#error You should define at least LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6 and LCD_PIN_D7 for LCD_TEXT_4BIT!
#endif

#if defined(LCD_TEXT_8BIT) && \
  (!defined(LCD_PIN_RS) || !defined(LCD_PIN_ENABLE) \
  || !defined(LCD_PIN_D0) || !defined(LCD_PIN_D1) \
  || !defined(LCD_PIN_D2) || !defined(LCD_PIN_D3) \
  || !defined(LCD_PIN_D4) || !defined(LCD_PIN_D5) \
  || !defined(LCD_PIN_D6) || !defined(LCD_PIN_D7))
#error You should define at least LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6 and LCD_PIN_D7 for LCD_TEXT_8BIT!
#endif

#if (defined(LCD_BACKLIGHT_ONOFF) || defined(LCD_BACKLIGHT_PWM)) \
  && (!defined(LCD_PIN_BACKLIGHT))
#error You should define LCD_PIN_BACKLIGHT for LCD_BACKLIGHT_ONOFF or LCD_BACKLIGHT_PWM!
#endif

#include <LiquidCrystal.h>

#if defined(LCD_TEXT_4BIT)
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
  LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
#elif defined(LCD_TEXT_8BIT)
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
  LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3,
  LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
#endif

/*! \brief Initialization of LCD display itself
 */
void lcd_init_display() {
  lcd.begin(LCD_COLS, LCD_ROWS);
}

/*! \brief Initialization of LCD display backlight LED
 */
void lcd_init_backlight() {
#if defined(LCD_BACKLIGHT_ONOFF) || defined(LCD_BACKLIGHT_PWM)
  pinMode(LCD_PIN_BACKLIGHT, OUTPUT);
#if defined(LCD_BACKLIGHT_ONOFF)
  lcd_set_backlight(1);
#elif defined(LCD_BACKLIGHT_PWM)
  lcd_set_backlight(LCD_BL_PWM_INIT);
#endif
#endif
}

/*! \brief Set brightness of LCD display backlight LED
 */
void lcd_set_backlight(uint8_t brightness) {
#if defined(LCD_BACKLIGHT_NONE)
  brightness = brightness;
#elif defined(LCD_BACKLIGHT_ONOFF)
  digitalWrite(LCD_PIN_BACKLIGHT, brightness == 0? LOW: HIGH);
#elif defined(LCD_BACKLIGHT_PWM)
#if defined(LCD_BL_PWM_MAX)
  uint16_t real_brightness = (brightness * LCD_BL_PWM_MAX) >> 8;
  brightness = real_brightness;
#endif
  analogWrite(LCD_PIN_BACKLIGHT, brightness);
#endif
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

#endif//LCD_TEXT_4BIT||LCD_TEXT_8BIT
