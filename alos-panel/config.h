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
//#define LCD_I2C_ADDR        0x27

/* KBD Configuration */
#define KBD_NONE

#endif//CONFIG_H
