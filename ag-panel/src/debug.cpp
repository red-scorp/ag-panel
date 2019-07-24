/*!
  \file debug.cpp
  \brief AG-Panel Project debugging code
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "private.h"
#include "debug.h"

#if defined(DEBUG_HW_SERIAL) || defined(DEBUG_HW_SERIAL1) || defined(DEBUG_HW_SERIAL2) || defined(DEBUG_HW_SERIAL3) || defined(DEBUG_SW_SERIAL)

#if defined(DEBUG_HW_SERIAL)
#include <HardwareSerial.h>
#define DEBUG_PORT      Serial
#endif

#if defined(DEBUG_HW_SERIAL1)
#include <HardwareSerial.h>
#define DEBUG_PORT      Serial1
#endif

#if defined(DEBUG_HW_SERIAL2)
#include <HardwareSerial.h>
#define DEBUG_PORT      Serial2
#endif

#if defined(DEBUG_HW_SERIAL3)
#include <HardwareSerial.h>
#define DEBUG_PORT      Serial3
#endif

#if defined(DEBUG_SW_SERIAL)
#include "SoftwareSerial.h"
#define DEBUG_PORT      SoftwareSerial

#if !defined(DEBUG_PIN_TX) || !defined(DEBUG_PIN_RX)
#error You should define DEBUG_PIN_TX and DEBUG_PIN_RX for DEBUG_SW_SERIAL
#endif

SoftwareSerial SoftwareSerial(DEBUG_PIN_RX, DEBUG_PIN_TX);
#endif

#if !defined(DEBUG_BAUD)
#define DEBUG_BAUD      9600
#endif

void debug_init() {
#if !defined(DEBUG_HW_SERIAL)
  DEBUG_PORT.begin(DEBUG_BAUD);
#endif
}

void debug_putch(uint8_t txbyte) {
  DEBUG_PORT.write(txbyte);
}

void debug_puts(char *str) {
  while(str != NULL && *str != '\0')
    debug_putch(*str++);
}

#else

void debug_init() {
}

void debug_putch(uint8_t txbyte) {
  txbyte = txbyte;
}

void debug_puts(char *str) {
  str = str;
}

#endif
