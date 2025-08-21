/** @file I2CPCF8574TextLCD.h
    @brief AG-Panel Project I2C 4-bit text (hd44780) LCD interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "TemplateTextLCD.h"
#include <LiquidCrystal_I2C.h>

#if !defined(ARDUINO_ARCH_GD32V) && !defined(ARDUINO_ARCH_KENDRYTE)

/** @brief I2C Text LCD class

    This class implements a 4-bit text LCD display based on HD44780 and connected
    with a help of PCF8574(T/AT) I2C 8-bit digital I/O expander chip.
    This class implements it's own backlight control.
 */
class I2CPCF8574TextLCD: public TemplateTextLCD<LiquidCrystal_I2C> {

public:
    explicit I2CPCF8574TextLCD(
        uint8_t Columns,
        uint8_t Rows,
        uint8_t I2CAddress
    ): TemplateTextLCD<LiquidCrystal_I2C>(new LiquidCrystal_I2C(I2CAddress, Columns, Rows), Columns, Rows),
        m_I2CAddress(I2CAddress) {}
    virtual ~I2CPCF8574TextLCD() override {}

    /** @brief Set backlight in binary (on/off) form

        This function calls corresponding function of LiquidCrystal_I2C class instance.
    */
    void SetBacklight(
        bool on               /**< Backlight state in on/off format */
    ) override {
        if(on)
            m_LCD->backlight();
        else
            m_LCD->noBacklight();
    }

    /** @brief Set backlight brightness if supported

        This function enables LCD backlight if brightness is non-zero.
    */
    void SetBacklight(
        uint8_t brightness    /**< Backlight brightness value */
    ) override {
        SetBacklight(bool(brightness > 0? true: false));
    }

    /** @brief Set backlight RGB colors if supported

        This function enables LCD backlight if RGB is non-zero.
    */
    void SetBacklight(
        uint8_t red,          /**< Red color value */
        uint8_t green,        /**< Green color value */
        uint8_t blue          /**< Blue color value */
    ) override {
        SetBacklight(bool(red > 0 || green > 0 || blue > 0? true: false));
    }

    /** @brief Set backlight RGB colors if supported

        This function enables LCD backlight if RGB is non-zero.
    */
    void SetBacklight(
        uint32_t rgb          /**< RGB integer value */
    ) override {
        SetBacklight(bool(rgb > 0? true: false));
    }

protected:
    uint8_t m_I2CAddress;
};

#else
#warning 'I2CPCF8574TextLCD' is not implemented for GD32V and KENDRYTE platforms because it lacks of standard header 'Wire.h'!
#endif /* !ARDUINO_ARCH_GD32V && !ARDUINO_ARCH_KENDRYTE */
