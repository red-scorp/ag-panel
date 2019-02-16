/*!
  \file config.h
  \brief ALoS-Panel Project configuration file
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef CONFIG_H
#define CONFIG_H

/* FirmWare Configuration */
#define FW_NAME             "ALoS" /* Arduino LCD over Serial Panel */
#define FW_VERSION          __TIME__ " " __DATE__

/* UART Configuration */
#define UART_DIRECT
//#define UART_BUFFERED

#define UART_BAUD           9600

/* for UART_BUFFERED */
#define UART_BUF_SIZE       512

/* LCD Configuration */
#define LCD_4BIT
//#define LCD_8BIT
//#define LCD_I2C

//#define LCD_BACKLIGHT_NONE
//#define LCD_BACKLIGHT_ONOFF
#define LCD_BACKLIGHT_PWM

#define LCD_ROWS            2
#define LCD_COLS            16

/* for LCD_4BIT and LCD_8BIT */
#define LCD_PIN_RS          12
#define LCD_PIN_RW          11 // 255
#define LCD_PIN_ENABLE      10
#define LCD_PIN_BACKLIGHT   9
//#define LCD_PIN_D0          255
//#define LCD_PIN_D1          255
//#define LCD_PIN_D2          255
//#define LCD_PIN_D3          255
#define LCD_PIN_D4          5
#define LCD_PIN_D5          4
#define LCD_PIN_D6          3
#define LCD_PIN_D7          2

/* for LCD_I2C */
//#define LCD_I2C_ADDR        0x27

/* Keyboard Configuration */
#define KBD_NONE
//#define KBD_D_MATRIX
//#define KBD_A_JOYSTICK

#define KBD_ROWS            4
#define KBD_COLS            4

/* for KBD_D_MATRIX */
#define KBD_PIN_C1          13
#define KBD_PIN_C2          8
#define KBD_PIN_C3          7
#define KBD_PIN_C4          6
#define KBD_PIN_R1          A0
#define KBD_PIN_R2          A1
#define KBD_PIN_R3          A2
#define KBD_PIN_R4          A3

/* for KBD_A_JOYSTICK */
#define KBD_PIN_X           A0
#define KBD_PIN_Y           A1
#define KBD_PIN_BTN         13

#endif//CONFIG_H
