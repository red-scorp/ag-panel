/*!
  \file config.h
  \brief AG-Panel Project configuration file
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef CONFIG_H
#define CONFIG_H

/* Protocol Configuration */
/* ------------------------------------------------------------------------- */
#define PROT_LOSPANEL
//#define PROT_RAWSERIAL

/* UART Configuration */
/* ------------------------------------------------------------------------- */
#define UART_HARDWARE
//#define UART_HARDWARE1
//#define UART_HARDWARE2
//#define UART_HARDWARE3
//#define UART_SOFTWARE
//#define UART_NONE

//#define UART_BUFFERED

#define UART_BAUD           115200
/* Add proper 'Speed=????' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other UART_BAUD then 9600 */

/* LCD Configuration */
/* ------------------------------------------------------------------------- */
#define LCD_TEXT_4BIT
//#define LCD_TEXT_8BIT
//#define LCD_TEXT_I2C_PCF8574
//#define LCD_TEXT_I2C_AIP31068
//#define LCD_TEXT_I2C_RGB
//#define LCD_TEXT_SPI_AIP31068

#define LCD_ROWS            2
#define LCD_COLS            16
/* Add proper 'Size=?x?' to '[hd44780]' section of your '/etc/LCDd.conf' for selected LCD_ROWS and LCD_COLS */

//#define LCD_BACKLIGHT_NONE
//#define LCD_BACKLIGHT_ONOFF
#define LCD_BACKLIGHT_PWM
//#define LCD_BACKLIGHT_RGB_ONOFF
//#define LCD_BACKLIGHT_RGB_PWM
//#define LCD_BACKLIGHT_I2C_RGB_PWM
/* Add 'Backlight=yes' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other value LCD_BACKLIGHT_NONE */

/* Keyboard Configuration */
/* ------------------------------------------------------------------------- */
//#define KBD_NONE
//#define KBD_D_MATRIX
//#define KBD_A_JOYSTICK
#define KBD_A_KEYPAD
//#define KBD_ROTARY_ENCODER
//#define KBD_A_MATRIX
//#define KBD_I2C_RGB /* this option is added automatically if LCD_I2C_RGB is selected */
//#define KBD_I2C_C_MPR121_KEYPAD
//#define KBD_I2C_C_TTP229_KEYPAD
//#define KBD_BUTTON
//#define KBD_JOINED /* Enables use of several keyboards at once */
/* Add 'Keypad=yes' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other value then KBD_NONE */
/* Check for proper 'KeyMatrix_?_?=???' values for your '/etc/LCDd.conf' in kbd.h */

#include "config_adv.h"

#endif //CONFIG_H
