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
  lcd_write_display(txbyte);
  stamp_last_tx();
}

/*! \brief Send command to LCD display
 */
void lcd_command(uint8_t txbyte) {
  wait_from_last_tx(txbyte < 4? 2000: 40); /* for commands 1 - 3 wait for 2 ms, otherwise 40 us */
  lcd_command_display(txbyte);
  stamp_last_tx();
}
