/*!
  \file config.h
  \brief ALoS-Panel Project configuration file
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef CONFIG_H
#define CONFIG_H

/* FirmWare Configuration */
/* ------------------------------------------------------------------------- */
#define FW_NAME             "ALoS" /* Arduino LCD over Serial Panel */
#define FW_VERSION          __TIME__ " " __DATE__

/* UART Configuration */
/* ------------------------------------------------------------------------- */
#define UART_DIRECT
//#define UART_BUFFERED

#define UART_BAUD           115200
/* Add proper 'Speed=????' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other UART_BAUD then 9600 */

#ifdef UART_BUFFERED
#define UART_BUF_SIZE       512
#endif

/* LCD Configuration */
/* ------------------------------------------------------------------------- */
#define LCD_4BIT
//#define LCD_8BIT
//#define LCD_I2C

#define LCD_ROWS            2
#define LCD_COLS            16
/* Add proper 'Size=?x?' to '[hd44780]' section of your '/etc/LCDd.conf' for selected LCD_ROWS and LCD_COLS */

#if defined(LCD_4BIT) || defined(LCD_8BIT)
//#define LCD_BACKLIGHT_NONE
//#define LCD_BACKLIGHT_ONOFF
#define LCD_BACKLIGHT_PWM
/* Add 'Backlight=yes' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other value LCD_BACKLIGHT_NONE */

#define LCD_PIN_RS          8
#define LCD_PIN_RW          255
#define LCD_PIN_ENABLE      9
#define LCD_PIN_BACKLIGHT   10

#ifdef LCD_8BIT
#define LCD_PIN_D0          255
#define LCD_PIN_D1          255
#define LCD_PIN_D2          255
#define LCD_PIN_D3          255
#endif

#define LCD_PIN_D4          4
#define LCD_PIN_D5          5
#define LCD_PIN_D6          6
#define LCD_PIN_D7          7
#endif

#ifdef LCD_I2C
#define LCD_I2C_ADDR        0x27
#endif

#ifdef LCD_BACKLIGHT_PWM
#define LCD_BL_PWM_INIT     0x20
//#define LCD_BL_PWM_MAX      0x80
#endif

/* Keyboard Configuration */
/* ------------------------------------------------------------------------- */
//#define KBD_NONE
//#define KBD_D_MATRIX
//#define KBD_A_JOYSTICK
#define KBD_A_KEYPAD
/* Add 'Keypad=yes' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other value then KBD_NONE */
/* Check for proper 'KeyMatrix_?_?=???' values for your '/etc/LCDd.conf' in kbd.h */

#ifdef KBD_D_MATRIX
#define KBD_ROWS            4
#define KBD_COLS            4

#define KBD_PIN_C1          13
#define KBD_PIN_C2          8
#define KBD_PIN_C3          7
#define KBD_PIN_C4          6
#define KBD_PIN_R1          A0
#define KBD_PIN_R2          A1
#define KBD_PIN_R3          A2
#define KBD_PIN_R4          A3
#endif

#ifdef KBD_A_JOYSTICK
#define KBD_PIN_X           A0
#define KBD_PIN_Y           A1
#define KBD_PIN_BTN         3

#define KBD_X_CENTER        512
#define KBD_Y_CENTER        512
#define KBD_THRESHOLD       50
#endif

#ifdef KBD_A_KEYPAD
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
#endif

#endif//CONFIG_H
