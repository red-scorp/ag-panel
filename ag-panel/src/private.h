/*!
  \file private.h
  \brief AG-Panel Project private header
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#ifndef PRIVATE_H
#define PRIVATE_H

#include <Arduino.h>
#if defined(ARDUINO_ARCH_ESP32)
#include <analogWrite.h>
#endif

#undef UART /* Requered to compile for DUE board */

const uint8_t InvalidPin = 255;

#endif//PRIVATE_H
