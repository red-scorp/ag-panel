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

const uint8_t PWMResolution = 8;
const int MaxPWMValue = (1 << PWMResolution) - 1;

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_ESP8266)
  const uint8_t AnalogResolution = 10;
#elif defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_ESP32)
  const uint8_t AnalogResolution = 12;
#else
  #warning The value of 'AnalogResolution' is not defined for this platform yet! Assuming 10-bit!
  const uint8_t AnalogResolution = 10;
#endif

const int MaxAnalogValue = (1 << AnalogResolution) - 1;


#endif//PRIVATE_H
