/*!
  \file lcd.cpp
  \brief AG-Panel Project LCD code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "lcd.h"
#include "../version.h"
#include "../uart/uart.h"
#include "../prot/prot.h"

#include "AbstractLCD.h"

/* LCD Configuration sanity check */
#if (!defined(LCD_TEXT_4BIT) && !defined(LCD_TEXT_8BIT) && !defined(LCD_TEXT_I2C) && !defined(LCD_TEXT_I2C_RGB)) \
  || (defined(LCD_TEXT_4BIT) && defined(LCD_TEXT_8BIT)) \
  || (defined(LCD_TEXT_4BIT) && defined(LCD_TEXT_I2C)) \
  || (defined(LCD_TEXT_4BIT) && defined(LCD_TEXT_I2C_RGB)) \
  || (defined(LCD_TEXT_8BIT) && defined(LCD_TEXT_I2C)) \
  || (defined(LCD_TEXT_8BIT) && defined(LCD_TEXT_I2C_RGB)) \
  || (defined(LCD_TEXT_I2C) && defined(LCD_TEXT_I2C_RGB))
#error You should define LCD_TEXT_4BIT, LCD_TEXT_8BIT, LCD_TEXT_I2C or LCD_TEXT_I2C_RGB and only one of them!
#endif

#if !defined(LCD_ROWS) || !defined(LCD_COLS)
#error You should define LCD_ROWS and LCD_COLS!
#endif

/*! \brief Initialization of LCD display
 */
void lcd_init() {
  lcd_init_display();
  lcd_init_backlight();
}

/*! \brief Write welcome message on LCD display
 */
void lcd_welcome() {
  char str[LCD_COLS + 1];
  uint8_t center_x = (LCD_COLS - 16) / 2;
  uint8_t center_y = (LCD_ROWS - 2) / 2;
  memset(str, 0, sizeof(str));
  lcd_clear_display();
  lcd_set_cursor(center_x, center_y);
  lcd_print_string(FW_NAME " v" FW_VERSION);
  lcd_set_cursor(center_x, center_y + 1);
  snprintf(str, LCD_COLS, "@%ldBd Ready", UART_BAUD);
  lcd_print_string(str);
}
