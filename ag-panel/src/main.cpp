/*!
  \file main.cpp
  \brief AG-Panel Project main code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "../config.h"
#include "version.h"

/*#include "prot/prot.h"
#include "uart/uart.h"
#include "lcd/lcd.h"
#include "kbd/kbd.h"
#include "debug.h"*/

#include "uart/all.h"
#include "lcd/all.h"
#include "kbd/all.h"
#include "prot/all.h"

static AbstractUART *s_UART = nullptr;
static AbstractLCD *s_LCD = nullptr;
static AbstractKeyboard *s_Keyboard = nullptr;
static AbstractProtocol *s_Protocol = nullptr;

void print_welcome() {
  char *str = new char[s_LCD->GetColumns() + 1];
  uint8_t center_x = (s_LCD->GetColumns() - 16) / 2;
  uint8_t center_y = (s_LCD->GetRows() - 2) / 2;
  memset(str, 0, s_LCD->GetColumns() + 1);
  s_LCD->Clear();
  s_LCD->SetCursor(center_x, center_y);
  s_LCD->Print(FW_NAME " v" FW_VERSION);
  s_LCD->SetCursor(center_x, center_y + 1);
  snprintf(str, s_LCD->GetColumns(), "@%ldBd Ready", s_UART->GetBaudRate());
  s_LCD->Print(str);
  delete [] str;
}

/*! \brief Main initialization function
 * - setup debugging
 * - setup UART
 * - setup LCD
 * - setup keyboard
 * - setup protocol
 */
void setup() {

  // debug_init();
  //
  // uart_init();
  // lcd_init();
  // lcd_welcome();
  // kbd_init();
  //
  // prot_init();

#if defined(UART_DIRECT)
  s_UART = new HardwareUART(UART_BAUD);
#elif defined(UART_BUFFERED)
  s_UART = new BufferedUART(new HardwareUART(UART_BAUD), UART_BUF_SIZE);
#else
  #error UART is not defined!
#endif

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
    s_LCD = new PPITextLCD(Backlight, LCD_COLS, LCD_ROWS,
      LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
      LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
  #elif defined(LCD_TEXT_8BIT)
    s_LCD = new PPITextLCD(Backlight, LCD_COLS, LCD_ROWS,
      LCD_PIN_RS, LCD_PIN_RW, LCD_PIN_ENABLE,
      LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3,
      LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);
  #endif
#elif defined(LCD_TEXT_I2C)
  s_LCD = new I2CTextLCD(LCD_COLS, LCD_ROWS, LCD_I2C_ADDR);
#elif defined(LCD_TEXT_I2C_RGB)
  s_LCD = new I2CRGBTextLCD(LCD_COLS, LCD_ROWS, 123);
#else
  #error LCD is not defined!
#endif

#if defined(KBD_NONE)
  s_Keyboard = new NoneKeyboard();
#elif defined(KBD_D_MATRIX)
  static const uint8_t cols[] = {
  #if KBD_COLS >= 1
    KBD_PIN_C1,
    #if KBD_COLS >= 2
      KBD_PIN_C2,
      #if KBD_COLS >= 3
        KBD_PIN_C3,
        #if KBD_COLS >= 4
          KBD_PIN_C4,
          #if KBD_COLS >= 5
            #error Only 4 Columns are supported for now
          #endif
        #endif
      #endif
    #endif
  #endif
  };
  static const uint8_t rows[] = {
  #if KBD_ROWS >= 1
    KBD_PIN_R1,
    #if KBD_ROWS >= 2
      KBD_PIN_R2,
      #if KBD_ROWS >= 3
        KBD_PIN_R3,
        #if KBD_ROWS >= 4
          KBD_PIN_R4,
          #if KBD_ROWS >= 5
            #error Only 4 Rows are supported for now
          #endif
        #endif
      #endif
    #endif
  #endif
  };
  s_Keyboard = new DigitalMatrix(KBD_COLS, KBD_ROWS, cols, rows);
#elif defined(KBD_A_JOYSTICK)
  s_Keyboard = new AnalogJoystick(KBD_PIN_X, KBD_PIN_Y, KBD_PIN_BTN);
#elif defined(KBD_A_KEYPAD)
  s_Keyboard = new AnalogKeypad(KBD_PIN_DATA);
#elif defined(KBD_ROTARY_ENCODER)
  s_Keyboard = new RotaryEncoder(KBD_PIN_D1, KBD_PIN_D2, KBD_PIN_BTN);
#elif defined(KBD_A_MATRIX)
  static const uint16_t data_array[KBD_ROWS * KBD_COLS] = KBD_DATA_ARRAY;
  s_Keyboard = new AnalogMatrix(KBD_COLS, KBD_ROWS, data_array, KBD_PIN_DATA);
#elif defined(KBD_I2C_RGB)
  s_Keyboard = new I2CRGBKeypad();
#elif defined(KBD_I2C_C_MATRIX)
  s_Keyboard = new I2CCapacitiveMatrix(KBD_COLS, KBD_ROWS, KBD_I2C_ADDR);
#else
  #error Keyboard is not defined!
#endif

#if defined(PROT_LOSPANEL)
  s_Protocol = new LoSPanelProtocol(s_UART, (AbstractTextLCD*)s_LCD, s_Keyboard);
#else
  #error Protocol is not defined!
#endif

  print_welcome();
}

/*! \brief Main loop function
 * - run protocol
 * - start background task
 */
void loop() {

  // prot_loop();
  // prot_yield();

  s_Protocol->Loop();
  s_Protocol->Yield();
}

/*! \brief Background task function */
void yield() {

  // prot_yield();

  s_Protocol->Yield();
}
