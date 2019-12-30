/*!
  \file main.cpp
  \brief AG-Panel Project main code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "../config.h"
#include "version.h"

#include "debug.h"

#include "uart/all.h"
#include "lcd/all.h"
#include "keyboard/all.h"
#include "protocol/all.h"

AbstractUART *g_DebugUART = nullptr;
static AbstractUART *s_UART = nullptr;
static AbstractLCD *s_LCD = nullptr;
static AbstractKeyboard *s_Keyboard = nullptr;
static AbstractProtocol *s_Protocol = nullptr;

/*!
  \brief Print welcome message to the LCD

  This function prints project name, project version and UART baud rate to the attached LCD.
 */
void print_welcome() {
  char str[s_LCD->GetColumns() + 1];
  uint8_t center_x = (s_LCD->GetColumns() - 16) / 2;
  uint8_t center_y = (s_LCD->GetRows() - 2) / 2;
  memset(str, 0, sizeof(str));
  s_LCD->Clear();
  s_LCD->SetBacklight(bool(true));
  s_LCD->SetCursor(center_x, center_y);
  snprintf(str, sizeof(str) - 1, FW_NAME " v" FW_VERSION);
  s_LCD->Print(str);
  DEBUG_STR("LCD> "); DEBUG_STR(str); DEBUG_STR("\n");
  s_LCD->SetCursor(center_x, center_y + 1);
  snprintf(str, sizeof(str) - 1, "@%ldBd Ready", s_UART->GetBaudRate());
  s_LCD->Print(str);
  DEBUG_STR("LCD> "); DEBUG_STR(str); DEBUG_STR("\n");
}

/*!
  \brief Main initialization function

 - setup debugging
 - setup UART
 - setup LCD
 - setup keyboard
 - setup protocol
 */
void setup() {

  #if defined(DEBUG_UART_HARDWARE)
    g_DebugUART = new HardwareUART(DEBUG_BAUD);
  #elif defined(DEBUG_UART_HARDWARE1)
    g_DebugUART = new HardwareUART(DEBUG_BAUD, 1);
  #elif defined(DEBUG_UART_HARDWARE2)
    g_DebugUART = new HardwareUART(DEBUG_BAUD, 2);
  #elif defined(DEBUG_UART_HARDWARE3)
    g_DebugUART = new HardwareUART(DEBUG_BAUD, 3);
  #elif defined(DEBUG_UART_SOFTWARE)
    g_DebugUART = new SoftwareUART(DEBUG_BAUD, DEBUG_PIN_RX, DEBUG_PIN_TX);
  #elif defined(DEBUG_UART_NONE)
    g_DebugUART = new NoneUART(DEBUG_BAUD);
  #else
    #error Debug UART is not defined!
  #endif

  DEBUG_STR("Starting Up...\n");
  DEBUG_STR("Initializing UART...\n");

  #if defined(UART_HARDWARE)
    s_UART = new HardwareUART(UART_BAUD);
  #elif defined(UART_HARDWARE1)
    s_UART = new HardwareUART(UART_BAUD, 1);
  #elif defined(UART_HARDWARE2)
    s_UART = new HardwareUART(UART_BAUD, 2);
  #elif defined(UART_HARDWARE3)
    s_UART = new HardwareUART(UART_BAUD, 3);
  #elif defined(UART_SOFTWARE)
    s_UART = new SoftwareUART(UART_BAUD, UART_PIN_RX, UART_PIN_TX);
  #elif defined(UART_NONE)
    s_UART = new NoneUART(UART_BAUD);
  #else
    #error UART is not defined!
  #endif

  #if defined(UART_BUFFERED)
    s_UART = new BufferedUART(s_UART, UART_BUF_SIZE);
  #endif

  #if defined(DEBUG_UART_STR)
    s_UART = new TextLoggingUART(s_UART, g_DebugUART);
  #endif

  DEBUG_STR("Initializing Backlight...\n");

  AbstractBacklight *Backlight = nullptr;
  #if defined(LCD_BACKLIGHT_NONE)
    Backlight = new NoneBacklight();
  #elif defined(LCD_BACKLIGHT_ONOFF)
    Backlight = new BinaryBacklight(LCD_PIN_BACKLIGHT);
  #elif defined(LCD_BACKLIGHT_PWM)
    #if defined(LCD_BL_PWM_MAX)
      Backlight = new PWMBacklight(LCD_PIN_BACKLIGHT, LCD_BL_PWM_MAX);
    #else
      Backlight = new PWMBacklight(LCD_PIN_BACKLIGHT);
    #endif
  #elif defined(LCD_BACKLIGHT_RGB_ONOFF)
    Backlight = new RGBBinaryBacklight(LCD_PIN_BACKLIGHT_R, LCD_PIN_BACKLIGHT_G, LCD_PIN_BACKLIGHT_B);
  #elif defined(LCD_BACKLIGHT_RGB_PWM)
    #if defined(LCD_BL_PWM_MAX)
      Backlight = new RGBPWMBacklight(LCD_PIN_BACKLIGHT_R, LCD_PIN_BACKLIGHT_G, LCD_PIN_BACKLIGHT_B, LCD_BACKLIGHT_COLOR, LCD_BL_PWM_MAX);
    #else
      Backlight = new RGBPWMBacklight(LCD_PIN_BACKLIGHT_R, LCD_PIN_BACKLIGHT_G, LCD_PIN_BACKLIGHT_B, LCD_BACKLIGHT_COLOR);
    #endif
  #endif

  DEBUG_STR("Initializing LCD...\n");

  #if defined(LCD_TEXT_4BIT) || defined(LCD_TEXT_8BIT)
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
    s_LCD = new I2CRGBTextLCD(LCD_COLS, LCD_ROWS, 123, LCD_BACKLIGHT_COLOR);
  #else
    #error LCD is not defined!
  #endif

  DEBUG_STR("Initializing Keyboard...\n");

  #if defined(KBD_JOINED)
    JoinedKeyboard *p_JoinedKeyboard = new JoinedKeyboard();
  #endif

  #if defined(KBD_NONE)
    s_Keyboard = new NoneKeyboard();
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_D_MATRIX)
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
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_JOYSTICK)
    s_Keyboard = new AnalogJoystick(KBD_PIN_X, KBD_PIN_Y, KBD_PIN_BTN);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_KEYPAD)
    s_Keyboard = new AnalogKeypad(KBD_PIN_DATA);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_ROTARY_ENCODER)
    s_Keyboard = new RotaryEncoder(KBD_PIN_D1, KBD_PIN_D2, KBD_PIN_BTN);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_A_MATRIX)
    static const uint16_t data_array[KBD_ROWS * KBD_COLS] = KBD_DATA_ARRAY;
    s_Keyboard = new AnalogMatrix(KBD_COLS, KBD_ROWS, data_array, KBD_PIN_DATA);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_RGB)
    #if !defined(LCD_TEXT_I2C_RGB)
      #error 'KBD_I2C_RGB' must be defined together with 'LCD_TEXT_I2C_RGB'!
    #endif
    s_Keyboard = new I2CRGBKeypad(s_LCD);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_C_MPR121_KEYPAD)
    s_Keyboard = new I2CMPR121CapacitiveKeypad(KBD_KEYS, KBD_I2C_ADDR);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_I2C_C_TTP229_KEYPAD)
    s_Keyboard = new I2CTTP229CapacitiveKeypad(KBD_KEYS, KBD_I2C_ADDR);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
  #if defined(KBD_BUTTON)
    static const uint8_t pins[] = KBD_PIN_ARRAY;
    s_Keyboard = new SimpleButton(KBD_NUM, pins);
    #if defined(KBD_JOINED)
      p_JoinedKeyboard->AddKeyboard(s_Keyboard);
      s_Keyboard = nullptr;
    #endif
  #endif
//  #else
//    #error Keyboard is not defined!
//  #endif

  #if defined(KBD_JOINED)
    s_Keyboard = p_JoinedKeyboard;
  #endif

  /* TODO: Add AbstractSpeaker and other classes for notice, warning and error sounds??? */

  DEBUG_STR("Initializing Protocol...\n");

  #if defined(PROT_LOSPANEL)
    s_Protocol = new LoSPanelProtocol(s_UART, (AbstractTextLCD*)s_LCD, s_Keyboard);
  #else
    #error Protocol is not defined!
  #endif

  print_welcome();
}

/*!
  \brief Main loop function

 - run protocol
 - start background task
 */
void loop() {

  if(s_Protocol != nullptr) {
    s_Protocol->Loop();
    s_Protocol->Yield();
  }
}

/*!
  \brief Background task function
 */
void yield() {

  if(s_Protocol != nullptr)
    s_Protocol->Yield();
}
