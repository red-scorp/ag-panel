/*!
  \file config_adv.h
  \brief AG-Panel Project advanced configuration file
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef CONFIG_ADV_H
#define CONFIG_ADV_H

#include "config.h"

/* UART Configuration */
/* ------------------------------------------------------------------------- */
#if defined(UART_BUFFERED)
#define UART_BUF_SIZE       512
#endif //UART_BUFFERED

#if defined(UART_SOFTWARE)
#define UART_PIN_RX         12
#define UART_PIN_TX         13
#endif //UART_SOFTWARE

/* LCD Configuration */
/* ------------------------------------------------------------------------- */
#if defined(LCD_TEXT_4BIT) || defined(LCD_TEXT_8BIT)
#define LCD_PIN_RS          8
#define LCD_PIN_RW          InvalidPin
#define LCD_PIN_ENABLE      9

#if defined(LCD_TEXT_8BIT)
#define LCD_PIN_D0          A0
#define LCD_PIN_D1          A1
#define LCD_PIN_D2          A2
#define LCD_PIN_D3          A3
#endif //LCD_TEXT_8BIT

#define LCD_PIN_D4          4
#define LCD_PIN_D5          5
#define LCD_PIN_D6          6
#define LCD_PIN_D7          7
#endif //LCD_TEXT_4BIT || LCD_TEXT_8BIT

#if defined(LCD_TEXT_I2C_PCF8574)
#define LCD_I2C_ADDR        0x27
#endif //LCD_TEXT_I2C_PCF8574

#if defined(LCD_TEXT_I2C_AIP31068)
#define LCD_I2C_ADDR        0x3E
#endif //LCD_TEXT_I2C_AIP31068

#if defined(LCD_TEXT_I2C_RGB)
//#define LCD_I2C_ADDR        0x57
#define KBD_I2C_RGB
#endif //LCD_TEXT_I2C_RGB

#if defined(LCD_BACKLIGHT_RGB_ONOFF) || defined(LCD_BACKLIGHT_RGB_PWM) || defined(LCD_TEXT_I2C_RGB)
#define LCD_BACKLIGHT_COLOR 0x00FFFFFF /* Bitmask: 0x00BBGGRR - red, green, blue */
#endif //LCD_BACKLIGHT_RGB_ONOFF || LCD_BACKLIGHT_RGB_PWM || LCD_TEXT_I2C_RGB

#if defined(LCD_BACKLIGHT_ONOFF) || defined(LCD_BACKLIGHT_PWM)
#define LCD_PIN_BACKLIGHT   10
#endif //LCD_BACKLIGHT_ONOFF || LCD_BACKLIGHT_PWM

#if defined(LCD_BACKLIGHT_RGB_ONOFF) || defined(LCD_BACKLIGHT_RGB_PWM)
#define LCD_PIN_BACKLIGHT_R 10
#define LCD_PIN_BACKLIGHT_G 11
#define LCD_PIN_BACKLIGHT_B 3
#endif //LCD_BACKLIGHT_RGB_ONOFF || LCD_BACKLIGHT_RGB_PWM

#if defined(LCD_BACKLIGHT_PWM) || defined(LCD_BACKLIGHT_RGB_PWM)
#define LCD_BL_PWM_INIT     0x20
//#define LCD_BL_PWM_MAX      0x80
#endif //LCD_BACKLIGHT_PWM

/* Keyboard Configuration */
/* ------------------------------------------------------------------------- */
#if defined(KBD_D_MATRIX)
#define KBD_ROWS            4
#define KBD_COLS            4

#define KBD_PIN_C1          A0
#define KBD_PIN_C2          A1
#define KBD_PIN_C3          A2
#define KBD_PIN_C4          A3
#define KBD_PIN_R1          A4
#define KBD_PIN_R2          A5
#define KBD_PIN_R3          A6
#define KBD_PIN_R4          A7
#endif //KBD_D_MATRIX

#if defined(KBD_A_JOYSTICK)
#define KBD_PIN_X           A0
#define KBD_PIN_Y           A1
#define KBD_PIN_BTN         12

#define KBD_X_CENTER        512
#define KBD_Y_CENTER        512
#define KBD_THRESHOLD       50
#endif //KBD_A_JOYSTICK

#if defined(KBD_A_KEYPAD)
#define KBD_PIN_DATA        A0

#define KBD_DATA_NONE_MIN   700
#define KBD_DATA_NONE_MAX   1023
#define KBD_DATA_UP_MIN     50
#define KBD_DATA_UP_MAX     150
#define KBD_DATA_DOWN_MIN   150
#define KBD_DATA_DOWN_MAX   350
#define KBD_DATA_LEFT_MIN   350
#define KBD_DATA_LEFT_MAX   550
#define KBD_DATA_RIGHT_MIN  0
#define KBD_DATA_RIGHT_MAX  50
#define KBD_DATA_SELECT_MIN 550
#define KBD_DATA_SELECT_MAX 700
#endif //KBD_A_KEYPAD

#if defined(KBD_ROTARY_ENCODER)
#define KBD_PIN_D1          2
#define KBD_PIN_D2          3
#define KBD_PIN_BTN         11
#endif //KBD_ROTARY_ENCODER

#if defined(KBD_A_MATRIX)
#define KBD_ROWS            4
#define KBD_COLS            4

#define KBD_PIN_DATA        A0

#define KBD_DATA_TOLERANCE  25
#define KBD_DATA_ARRAY      {1023, 930, 850, 790, \
                             680, 640, 600, 570, \
                             512, 487, 465, 445, \
                             410, 330, 277, 238}
/*#define KBD_DATA_ARRAY      {1023, 930, 850, \
                             790, 730, 680, \
                             640, 600, 570, \
                             540, 510, 490}*/
#endif //KBD_A_MATRIX

#if defined(KBD_I2C_C_MPR121_KEYPAD)
#define KBD_KEYS            12

#define KBD_I2C_ADDR        0x5A
#endif //KBD_I2C_C_MPR121_KEYPAD

#if defined(KBD_I2C_C_TTP229_KEYPAD)
#define KBD_KEYS            16

#define KBD_I2C_ADDR        0x57
#endif //KBD_I2C_C_TTP229_KEYPAD

#if defined(KBD_BUTTON)
#define KBD_NUM             1

#define KBD_PIN_ARRAY       {A1}
#endif //KBD_BUTTON

#endif //CONFIG_ADV_H
