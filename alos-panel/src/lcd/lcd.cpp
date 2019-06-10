/*!
  \file lcd.cpp
  \brief ALoS-Panel Project LCD code
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
  \note https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
*/

#include "../private.h"
#include "lcd.h"

/* LCD Configuration sanity check */
#if (!defined(LCD_4BIT) && !defined(LCD_8BIT) && !defined(LCD_I2C) && !defined(LCD_I2C_RGB)) \
  || (defined(LCD_4BIT) && defined(LCD_8BIT)) \
  || (defined(LCD_4BIT) && defined(LCD_I2C)) \
  || (defined(LCD_4BIT) && defined(LCD_I2C_RGB)) \
  || (defined(LCD_8BIT) && defined(LCD_I2C)) \
  || (defined(LCD_8BIT) && defined(LCD_I2C_RGB)) \
  || (defined(LCD_I2C) && defined(LCD_I2C_RGB))
#error You should define LCD_4BIT, LCD_8BIT, LCD_I2C or LCD_I2C_RGB and only one of them!
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
  (!defined(LCD_BACKLIGHT_COLOR))
#error You should define LCD_BACKLIGHT_COLOR for LCD_I2C_RGB!
#endif

#if defined(LCD_I2C__RGB) && \
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
#elif defined(LCD_I2C_RGB)
#include <Adafruit_RGBLCDShield.h>
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
#elif defined(LCD_I2C_RGB)
Adafruit_RGBLCDShield lcd;
#endif

/*! \brief Initialization of LCD display
 */
void lcd_init() {
#if defined(LCD_4BIT) || defined(LCD_8BIT)
  lcd.begin(LCD_ROWS, LCD_COLS);
#elif defined(LCD_I2C)
  lcd.init();
#elif defined(LCD_I2C_RGB)
  lcd.begin(LCD_ROWS, LCD_COLS);
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

/*! \brief Last LCD transfer microseconds time stamp value
 */
static uint32_t lcd_last_tx_micros = 0;

/*! \brief Wait for given microseconds from last LCD transfer
 */
static void wait_from_last_tx(uint32_t wait_micros) {
  uint32_t wait_for_micros = lcd_last_tx_micros + wait_micros;

  if((wait_for_micros > lcd_last_tx_micros) && (micros() >= wait_for_micros)) /* we are already over the target time */
    return;

//  digitalWrite(LED_BUILTIN, HIGH);

  if(wait_for_micros < lcd_last_tx_micros) { /* we have an micros() overflow */
    while(micros() > lcd_last_tx_micros) /* first run over the maximum */
      los_yield();
  }

  while(micros() < wait_for_micros) /* now wait for target time */
    los_yield();

//  digitalWrite(LED_BUILTIN, LOW);
}

/*! \brief Store last LCD transfer time stamp
 */
static void stamp_last_tx() {
  lcd_last_tx_micros = micros();
}

/*! \brief Write character to LCD display
 */
void lcd_write(uint8_t txbyte) {
  wait_from_last_tx(40);
  lcd.write(txbyte);
  stamp_last_tx();
}

/*! \brief Send command to LCD display
 */
void lcd_command(uint8_t txbyte) {
  wait_from_last_tx(txbyte < 4? 2000: 40); /* for commands 1 - 3 wait for 2 ms, otherwise 40 us */
  lcd.command(txbyte);
  stamp_last_tx();
}

/*! \brief Initialization of LCD display backlight LED
 */
void lcd_init_backlight() {
#if defined(LCD_4BIT) || defined(LCD_8BIT)
#if defined(LCD_BACKLIGHT_ONOFF) || defined(LCD_BACKLIGHT_PWM)
  pinMode(LCD_PIN_BACKLIGHT, OUTPUT);
#if defined(LCD_BACKLIGHT_ONOFF)
  lcd_set_backlight(1);
#elif defined(LCD_BACKLIGHT_PWM)
  lcd_set_backlight(LCD_BL_PWM_INIT);
#endif
#endif
#elif defined(LCD_I2C)
  lcd.backlight();
#elif defined(LCD_I2C_RGB)
  lcd.setBacklight(LCD_BACKLIGHT_COLOR);
#endif
}

/*! \brief Set brightness of LCD display backlight LED
 */
void lcd_set_backlight(uint8_t brightness) {
#if defined(LCD_4BIT) || defined(LCD_8BIT)
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
#elif defined(LCD_I2C)
  if(brightness == 0)
    lcd.noBacklight();
  else
    lcd.backlight();
#elif defined(LCD_I2C_RGB)
  if(brightness == 0)
    lcd.setBacklight(0); /* does it work? */
  else
    lcd.setBacklight(LCD_BACKLIGHT_COLOR);
#endif
}
