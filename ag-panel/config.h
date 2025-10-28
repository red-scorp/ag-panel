/** @file config.h
    @brief AG-Panel Project default configuration file
    @copyright (C) 2019-2025 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#ifndef UNIT_TEST

/* Protocol Configuration */
/* ------------------------------------------------------------------------- */
#if ! defined(PROT_LOSPANEL) && ! defined(PROT_RAWSERIAL)
#define PROT_LOSPANEL           /* Use LoS-panel protocol */
//#define PROT_RAWSERIAL          /* Use raw serial protocol */
#endif /* ! PROT_LOSPANEL && ! PROT_RAWSERIAL */

/* UART Configuration */
/* ------------------------------------------------------------------------- */
#if ! defined(UART_HARDWARE) && ! defined(UART_HARDWARE1) && ! defined(UART_HARDWARE2) && \
    ! defined(UART_HARDWARE3) && ! defined(UART_HARDWARE4) && ! defined(UART_HARDWARE5) && \
    ! defined(UART_HARDWARE6) && ! defined(UART_HARDWARE7) && ! defined(UART_HARDWARE8) && \
    ! defined(UART_HARDWARE9) && ! defined(UART_HARDWARE10) && ! defined(UART_HARDWAREUSB) && \
    ! defined(UART_SOFTWARE) && ! defined(UART_NONE)
#define UART_HARDWARE           /* Use Serial (usually UART0) for communication */
//#define UART_HARDWARE1          /* Use Serial1 (usually UART1) for communication */
//#define UART_HARDWARE2          /* Use Serial2 (usually UART2) for communication */
//#define UART_HARDWARE3          /* Use Serial3 (usually UART3) for communication */
//#define UART_HARDWARE4          /* Use Serial4 (usually UART4) for communication */
//#define UART_HARDWARE5          /* Use Serial5 (usually UART5) for communication */
//#define UART_HARDWARE6          /* Use Serial6 (usually UART6) for communication */
//#define UART_HARDWARE7          /* Use Serial7 (usually UART7) for communication */
//#define UART_HARDWARE8          /* Use Serial8 (usually UART8) for communication */
//#define UART_HARDWARE9          /* Use Serial9 (usually UART9) for communication */
//#define UART_HARDWARE10         /* Use Serial10 (usually UART10) for communication */
//#define UART_HARDWAREUSB        /* Use SerialUSB (usually virtual UART) for communication */
//#define UART_SOFTWARE           /* Use SoftwareSerial (any digital pins as UART) for communication */
//#define UART_NONE               /* Use no UART */
#endif /* ! UART_HARDWARE && ... */

#if ! defined(UART_BUFFERED)
//#define UART_BUFFERED           /* Use extra buffering for communication */
#endif /* ! UART_BUFFERED */

#if ! defined(UART_BAUD)
#define UART_BAUD           115200    /* Use given baud rate for communication */
/* Add proper 'Speed=????' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other UART_BAUD then 9600 */
#endif /* ! UART_BAUD */

/* LCD Configuration */
/* ------------------------------------------------------------------------- */
#if ! defined(LCD_TEXT_4BIT) && ! defined(LCD_TEXT_8BIT) && ! defined(LCD_TEXT_I2C_PCF8574) && \
    ! defined(LCD_TEXT_I2C_AIP31068) && ! defined(LCD_TEXT_I2C_RGB) && ! defined(LCD_TEXT_SPI_AIP31068)
#define LCD_TEXT_4BIT           /* Use HD44780 based text display in 4-bit mode */
//#define LCD_TEXT_8BIT           /* Use HD44780 based text display in 8-bit mode */
//#define LCD_TEXT_I2C_PCF8574    /* Use HD44780 based text display over I2C with help of PCF8574 IC */
//#define LCD_TEXT_I2C_AIP31068   /* Use HD44780 based text display over I2C with help of AIP31068 IC */
//#define LCD_TEXT_I2C_RGB        /* Use HD44780 based text RGB display over I2C with help of MCP23017 IC */
//#define LCD_TEXT_SPI_AIP31068   /* Use HD44780 based text display over SPI with help of AIP31068 IC */
#endif /* ! LCD_TEXT_4BIT && ... */

#if ! defined(LCD_ROWS) && ! defined(LCD_COLS)
#define LCD_ROWS            2   /* Use given number of text rows */
#define LCD_COLS            16  /* Use given number of text columns */
/* Add proper 'Size=?x?' to '[hd44780]' section of your '/etc/LCDd.conf' for selected LCD_ROWS and LCD_COLS */
#endif /* ! LCD_ROWS && ! LCD_COLS */

#if ! defined(LCD_BACKLIGHT_NONE) && ! defined(LCD_BACKLIGHT_ONOFF) && \
    ! defined(LCD_BACKLIGHT_PWM) && ! defined(LCD_BACKLIGHT_RGB_ONOFF) && \
    ! defined(LCD_BACKLIGHT_RGB_PWM) && ! defined(LCD_BACKLIGHT_I2C_RGB_PWM)
//#define LCD_BACKLIGHT_NONE        /* Use no controlled display backlight */
//#define LCD_BACKLIGHT_ONOFF       /* Use binary controlled display backlight */
#define LCD_BACKLIGHT_PWM         /* Use gradually controlled display backlight */
//#define LCD_BACKLIGHT_RGB_ONOFF   /* Use binary controlled RGB display backlight */
//#define LCD_BACKLIGHT_RGB_PWM     /* Use gradually controlled RGB display backlight */
//#define LCD_BACKLIGHT_I2C_RGB_PWM /* Use gradually controlled RGB display backlight over I2C with help of PCA9633 IC */
/* Add 'Backlight=yes' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other value LCD_BACKLIGHT_NONE */
#endif /* ! LCD_BACKLIGHT_NONE && ... */

//#define LCD_FONT_8X8_TEST

/* Keyboard Configuration */
/* ------------------------------------------------------------------------- */
#if ! defined(KBD_NONE) && ! defined(KBD_D_MATRIX) && ! defined(KBD_A_JOYSTICK) && \
    ! defined(KBD_A_KEYPAD) && ! defined(KBD_ROTARY_ENCODER) && ! defined(KBD_A_MATRIX) && \
    ! defined(KBD_I2C_RGB) && ! defined(KBD_I2C_C_MPR121_KEYPAD) && \
    ! defined(KBD_I2C_C_TTP229_KEYPAD) && ! defined(KBD_BUTTON) && ! defined(KBD_JOINED)
//#define KBD_NONE                  /* Use no keyboard */
//#define KBD_D_MATRIX              /* Use digital matrix keypad */
//#define KBD_A_JOYSTICK            /* Use analog joystick */
#define KBD_A_KEYPAD              /* Use analog (resistance value based) keypad */
//#define KBD_ROTARY_ENCODER        /* Use digital rotary encoder */
//#define KBD_A_MATRIX              /* Use analog (resistance value based) matrix shaped keypad */
//#define KBD_I2C_RGB               /* Use build-in keypad over I2C with help of MCP23017 IC. This option is added automatically if LCD_TEXT_I2C_RGB is selected */
//#define KBD_I2C_C_MPR121_KEYPAD   /* Use capacitive matrix shaped keypad over I2C with help of MPR121 IC */
//#define KBD_I2C_C_TTP229_KEYPAD   /* Use capacitive matrix shaped keypad over I2C with help of TTP229 IC */
//#define KBD_BUTTON                /* Use individual button(s) keypad */
//#define KBD_JOINED                /* Use several keyboards joined together */
/* Add 'Keypad=yes' to '[hd44780]' section of your '/etc/LCDd.conf' if you use any other value then KBD_NONE */
/* Check for proper 'KeyMatrix_?_?=???' values for your '/etc/LCDd.conf' in kbd.h */
#endif /* ! KBD_NONE && ... */

#else

#define PROT_RAWSERIAL
#define UART_UT
#define LCD_TEXT_UT
#define LCD_BACKLIGHT_UT
#define KBD_UT

#endif/*UNIT_TEST*/

#include "config_adv.h"
