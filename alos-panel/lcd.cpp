/*!
  \file lcd.cpp
  \brief ALoS-Panel Project LCD code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "lcd.h"

/* LCD Configuration sanity check */
#if (!defined(LCD_4BIT) && !defined(LCD_8BIT) && !defined(LCD_I2C)) \
  || (defined(LCD_4BIT) && defined(LCD_8BIT)) \
  || (defined(LCD_4BIT) && defined(LCD_I2C)) \
  || (defined(LCD_8BIT) && defined(LCD_I2C))
#error You should define LCD_4BIT, LCD_8BIT or LCD_I2C and only one of them!
#endif

#if defined(LCD_4BIT) || defined(LCD_8BIT)
#if (!defined(LCD_BACKLIGHT_NONE) && !defined(LCD_BACKLIGHT_ONOFF) && !defined(LCD_BACKLIGHT_PWM)) \
  || (defined(LCD_BACKLIGHT_NONE) && defined(LCD_BACKLIGHT_ONOFF)) \
  || (defined(LCD_BACKLIGHT_NONE) && defined(LCD_BACKLIGHT_PWM)) \
  || (defined(LCD_BACKLIGHT_ONOFF) && defined(LCD_BACKLIGHT_PWM))
#error You should define LCD_BACKLIGHT_NONE, LCD_BACKLIGHT_ONOFF or LCD_BACKLIGHT_PWM and only one of them!
#endif
#endif

#if !defined(LCD_ROWS) || !defined(LCD_COLS)
#error You should define LCD_ROWS and LCD_COLS!
#endif

#if defined(LCD_4BIT) && \
  (!defined(LCD_PIN_RS) || !defined(LCD_PIN_ENABLE) \
  || !defined(LCD_PIN_D4) || !defined(LCD_PIN_D5) \
  || !defined(LCD_PIN_D6) || !defined(LCD_PIN_D7))
#error You should define at least LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6 and LCD_PIN_D7 for LCD_4BIT!
#endif

#if defined(LCD_8BIT) && \
  (!defined(LCD_PIN_RS) || !defined(LCD_PIN_ENABLE) \
  || !defined(LCD_PIN_D0) || !defined(LCD_PIN_D1) \
  || !defined(LCD_PIN_D2) || !defined(LCD_PIN_D3) \
  || !defined(LCD_PIN_D4) || !defined(LCD_PIN_D5) \
  || !defined(LCD_PIN_D6) || !defined(LCD_PIN_D7))
#error You should define at least LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6 and LCD_PIN_D7 for LCD_8BIT!
#endif

#if defined(LCD_I2C) && \
  (!defined(LCD_I2C_ADDR))
#error You should define LCD_I2C_ADDR for LCD_I2C!
#endif

#if (defined(LCD_BACKLIGHT_ONOFF) || defined(LCD_BACKLIGHT_PWM)) \
  && (!defined(LCD_PIN_BACKLIGHT))
#error You should define LCD_PIN_BACKLIGHT for LCD_BACKLIGHT_ONOFF or LCD_BACKLIGHT_PWM!
#endif

#if defined(LCD_4BIT) || defined(LCD_8BIT)
#include <LiquidCrystal.h>
#elif defined(LCD_I2C)
#include <LiquidCrystal_I2C.h>
#endif

#if defined(LCD_4BIT)
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
  LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
#elif defined(LCD_8BIT)
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
  LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3,
  LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
#elif defined(LCD_I2C)
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS);
#endif

/*! \brief Initialization of LCD display
 */
void lcd_init() {
#if defined(LCD_4BIT) || defined(LCD_8BIT)
  lcd.begin(LCD_ROWS, LCD_COLS);
#elif defined(LCD_I2C)
  lcd.init();
#endif
  lcd_init_backlight();
}

/*! \brief Write welcome message on LCD display
 */
void lcd_welcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(FW_NAME " Ready...");
  lcd.setCursor(0, 1);
  lcd.print(FW_VERSION);
}

/*! \brief Write character to LCD display
 */
void lcd_write(uint8_t txbyte) {
  lcd.write(txbyte);
}

/*! \brief Send command to LCD display
 */
void lcd_command(uint8_t txbyte) {
  lcd.command(txbyte);
}

/*! \brief Initialization of LCD display backlight LED
 */
void lcd_init_backlight() {
#if defined(LCD_4BIT) || defined(LCD_8BIT)
#if defined(LCD_BACKLIGHT_ONOFF) || defined(LCD_BACKLIGHT_PWM)
  pinMode(LCD_PIN_BACKLIGHT, OUTPUT);
  lcd_set_backlight(LCD_BL_PWM_INIT);
#endif
#elif defined(LCD_I2C)
  lcd.backlight();
#endif
}

/*! \brief Set brightness of LCD display backlight LED
 */
void lcd_set_backlight(uint8_t brightness) {
#if defined(LCD_4BIT) || defined(LCD_8BIT)
#if defined(LCD_PIN_BACKLIGHT)
#if defined(LCD_BACKLIGHT_NONE)
  brightness = brightness;
#elif defined(LCD_BACKLIGHT_ONOFF)
  digitalWrite(LCD_PIN_BACKLIGHT, brightness == 0? LOW: HIGH);
#elif defined(LCD_BACKLIGHT_PWM)
  analogWrite(LCD_PIN_BACKLIGHT, brightness);
#endif
#endif
#elif defined(LCD_I2C)
  if(brightness == 0)
    lcd.noBacklight();
  else
    lcd.backlight();
#endif
}
