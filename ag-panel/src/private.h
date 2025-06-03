/** @file private.h
    @brief AG-Panel Project private header
    @copyright (C) 2019-2024 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#if !defined(UNIT_TEST)

#include <Arduino.h>

#if defined(__riscv) && !defined(ARDUINO_ARCH_ESP32)
    #if __INTPTR_WIDTH__ == 32
        #define ARDUINO_ARCH_GD32V
        /* TODO: add implementation of 'Wire.h' and 'SPI.h' for RISC-V */
        #define SCK   1     /* TODO: find out the real value */
        #define MOSI  1     /* TODO: find out the real value */
        #define MISO  1     /* TODO: find out the real value */
        #define A0    0     /* TODO: find out the real value */
    #endif
    #if __INTPTR_WIDTH__ == 64
        #define ARDUINO_ARCH_KENDRYTE
        /* TODO: add implementation of 'Wire.h' and 'SPI.h' for RISC-V */
        #define SCK   1     /* TODO: find out the real value */
        #define MOSI  1     /* TODO: find out the real value */
        #define MISO  1     /* TODO: find out the real value */
        #define A0    0     /* TODO: find out the real value */
    #endif
#endif

#undef UART /* Required to compile for DUE board */

#if defined(ARDUINO_ARCH_ESP32)
    #include "esp32-hal-spi.h"
#endif

#include "SPI.h"

/* Hack for Raspberry Pico */
#if !defined(SPI_CLOCK_DIV2)
    #define SPI_CLOCK_DIV2   2
    #define SPI_CLOCK_DIV4   4
    #define SPI_CLOCK_DIV8   8
    #define SPI_CLOCK_DIV16  16
    #define SPI_CLOCK_DIV32  32
    #define SPI_CLOCK_DIV64  64
    #define SPI_CLOCK_DIV128 128
#endif

const uint8_t InvalidPin = 255;

const uint8_t PWMResolution = 8;
const int MaxPWMValue = (1 << PWMResolution) - 1;

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_ESP8266)
    const uint8_t AnalogResolution = 10;
#elif defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_RP2040)
    const uint8_t AnalogResolution = 12;
#else
    #if defined(ADC_RESOLUTION)
        #warning Use macro 'ADC_RESOLUTION' for 'AnalogResolution' for this platform. Check the value for correctness.
        const uint8_t AnalogResolution = ADC_RESOLUTION;
    #else
        #warning The value of 'AnalogResolution' is not defined for this platform yet! Assuming 10-bit!
        const uint8_t AnalogResolution = 10;
    #endif/*ADC_RESOLUTION*/
#endif

#else/*UNIT_TEST*/

#include <stdint.h>

const uint8_t InvalidPin = 255;

const uint8_t PWMResolution = 8;
const int MaxPWMValue = (1 << PWMResolution) - 1;

const uint8_t AnalogResolution = 10;

#endif/*UNIT_TEST*/

const int MaxAnalogValue = (1 << AnalogResolution) - 1;

/* Some useful defines */
#define ITEMS_OF_ARRAY(arr)     (sizeof(arr) / sizeof(arr[0]))

/* Some compiler attribute defines */
#define A_UNUSED                __attribute__((unused))
#define A_ALIGN(bytes)          __attribute__((aligned(bytes)))
#define A_PACKED(bytes)         __attribute__((packed(bytes)))
#define A_NAKED                 __attribute__((naked))
#define A_NOINLINE              __attribute__((noinline))
#define A_ALWAYS_INLINE         __attribute__((always_inline))
#define A_NO_RETURN             __attribute__((noreturn))
#define A_OPTIMIZE(flag)        __attribute__((optimize(flag)))
#define A_NO_OPTIMIZE           A_OPTIMIZE("O0")
