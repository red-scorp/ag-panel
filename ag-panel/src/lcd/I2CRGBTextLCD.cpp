/** @file I2CRGBTextLCD.cpp
    @brief AG-Panel Project I2C RGB keypad's text (hd44780) LCD implementation
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "I2CRGBTextLCD.h"

#if !defined(ARDUINO_ARCH_GD32V) && !defined(ARDUINO_ARCH_KENDRYTE)

#include <Adafruit_RGBLCDShield.h>

/** @brief Initialization of I2C RGB text LCD display

    Configures I2C RGB text LCD display to work with specified geometry.
    @returns true
 */
bool I2CRGBTextLCD::Init() {
    m_Lowlevel = new Adafruit_RGBLCDShield;
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    p_I2CRGBLCD->begin(m_Columns, m_Rows);
    /* TODO: add usage of m_I2CAddress, currently it is ignored! */
    return true;
}

/** @brief Deinitialization of I2C RGB text LCD display class
 */
void I2CRGBTextLCD::Exit() {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    if(p_I2CRGBLCD != nullptr)
        delete p_I2CRGBLCD;
    m_Lowlevel = nullptr;
}

/** @brief Set backlight in binary (on/off) form

    This function sets default color of RGB backlight if enabled.
 */
void I2CRGBTextLCD::SetBacklight(
    bool on               /**< Backlight state in on/off format */
) {
    SetBacklight(uint32_t(on? m_DefaultColor: 0));
}

/** @brief Set backlight brightness if supported

    This function sets default color of RGB backlight if brightness is non-zero.
 */
void I2CRGBTextLCD::SetBacklight(
    uint8_t brightness    /**< Backlight brightness value */
) {
    SetBacklight(uint32_t(brightness > 0? m_DefaultColor: 0));
}

/** @brief Set backlight RGB colors if supported

    This function calls corresponding function of Adafruit_RGBLCDShield class instance.
 */
void I2CRGBTextLCD::SetBacklight(
    uint8_t red,          /**< Red color value */
    uint8_t green,        /**< Green color value */
    uint8_t blue          /**< Blue color value */
) {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    p_I2CRGBLCD->setBacklight((red > 0? 0x01: 0x00) | (green > 0? 0x02: 0x00) | (blue > 0? 0x04: 0x00));
}

/** @brief Set backlight RGB colors if supported

    This function sets RGB color based on given integer value.
 */
void I2CRGBTextLCD::SetBacklight(
    uint32_t rgb          /**< RGB integer value */
) {
    SetBacklight(RGBUint2Red(rgb), RGBUint2Green(rgb), RGBUint2Blue(rgb));
}

/** @brief Clear LCD display

    This function calls corresponding function of Adafruit_RGBLCDShield class instance.
 */
void I2CRGBTextLCD::Clear() {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    p_I2CRGBLCD->clear();
}

/** @brief Set Cursor on LCD display

    This function calls corresponding function of Adafruit_RGBLCDShield class instance.
 */
void I2CRGBTextLCD::SetCursor(
    uint8_t column,       /**< Column to put the cursor to */
    uint8_t row           /**< Row to put the cursor to */
) {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    p_I2CRGBLCD->setCursor(column, row);
}

/** @brief Print a text on LCD display

    This function calls corresponding function of Adafruit_RGBLCDShield class instance.
 */
void I2CRGBTextLCD::Print(
    const char *str       /**< String to print */
) {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    p_I2CRGBLCD->print(str);
}

/** @brief Print a character on LCD display

    This function calls corresponding function of Adafruit_RGBLCDShield class instance.
 */
void I2CRGBTextLCD::Print(
    char character        /**< Character to print */
) {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    p_I2CRGBLCD->print(character);
}

/** @brief Write a byte (RS = 1) to LCD display

    This function calls corresponding function of Adafruit_RGBLCDShield class instance.
 */
void I2CRGBTextLCD::Write(
    uint8_t byte          /**< Byte to write to LCD display */
) {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    p_I2CRGBLCD->write(byte);
}

/** @brief Send a command byte (RS = 0) to LCD display

    This function calls corresponding function of Adafruit_RGBLCDShield class instance.
 */
void I2CRGBTextLCD::Command(
    uint8_t byte          /**< Command to send to LCD display */
) {
    Adafruit_RGBLCDShield *p_I2CRGBLCD = reinterpret_cast<Adafruit_RGBLCDShield*>(m_Lowlevel);
    p_I2CRGBLCD->command(byte);
}

#else
#warning 'I2CRGBTextLCD' is not implemented for GD32V and KENDRYTE platforms because it lacks of standard header 'Wire.h'!
#endif /* !ARDUINO_ARCH_GD32V */
