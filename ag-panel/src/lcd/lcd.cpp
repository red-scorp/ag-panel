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
#include "../protocol/prot.h"

#if 0

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

#include "AbstractBacklight.h"
#include "AbstractLCD.h"
#include "AbstractTextLCD.h"

#include "NoneBacklight.h"
#include "BinaryBacklight.h"
#include "PWMBacklight.h"
#include "RGBPWMBacklight.h"
#include "RGBBinaryBacklight.h"

#include "PPITextLCD.h"
#include "I2CTextLCD.h"
#include "I2CRGBTextLCD.h"

static AbstractTextLCD *LCD = nullptr;

void lcd_init_display() {
#if defined(LCD_TEXT_4BIT) || defined(LCD_TEXT_8BIT)
  AbstractBacklight *Backlight = nullptr;
  #if defined(LCD_BACKLIGHT_NONE)
    Backlight = new NoneBacklight(LCD_PIN_BACKLIGHT);
  #elif defined(LCD_BACKLIGHT_ONOFF)
    Backlight = new BinaryBacklight(LCD_PIN_BACKLIGHT);
  #elif defined(LCD_BACKLIGHT_PWM)
    #if defined(LCD_BL_PWM_MAX)
      Backlight = new PWMBacklight(LCD_PIN_BACKLIGHT, LCD_BL_PWM_MAX);
    #else
      Backlight = new PWMBacklight(LCD_PIN_BACKLIGHT);
    #endif
  #endif
  #if defined(LCD_TEXT_4BIT)
    LCD = new PPITextLCD(Backlight, LCD_COLS, LCD_ROWS,
      LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
      LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
  #elif defined(LCD_TEXT_8BIT)
    LCD = new PPITextLCD(Backlight, LCD_COLS, LCD_ROWS,
      LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
      LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3,
      LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
  #endif
#elif defined(LCD_TEXT_I2C)
  LCD = new I2CTextLCD(LCD_COLS, LCD_ROWS, LCD_I2C_ADDR);
#elif defined(LCD_TEXT_I2C_RGB)
  LCD = new I2CRGBTextLCD(LCD_COLS, LCD_ROWS, 123);
#else
#error Not defined!
#endif
}

void lcd_init_backlight() {
#ifdef LCD_BL_PWM_INIT
  LCD->SetBacklight(uint8_t(LCD_BL_PWM_INIT));
#endif
}

void lcd_set_backlight(uint8_t brightness) {
  LCD->SetBacklight(brightness);
}

void lcd_write_display(uint8_t txbyte) {
  LCD->Write(txbyte);
}

void lcd_command_display(uint8_t txbyte) {
  LCD->Command(txbyte);
}

void lcd_clear_display() {
  LCD->Clear();
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
  LCD->SetCursor(col, row);
}

void lcd_print_string(const char *str) {
  LCD->Print(str);
}

#endif
