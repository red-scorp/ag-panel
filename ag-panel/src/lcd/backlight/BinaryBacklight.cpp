/*! \file BinaryBacklight.cpp
    \brief AG-Panel Project binary (on/off) backlight implementation
    \copyright (C) 2019-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../../private.h"
#include "BinaryBacklight.h"

/*! \brief Initialization of binary backlight

    Configures binary backlight digital pin.
    \returns true
 */
bool BinaryBacklight::Init() {
    pinMode(m_LEDPin, OUTPUT);
    return true;
}

/*! \brief Deinitialization of binary backlight class
 */
void BinaryBacklight::Exit() {
}

/*! \brief Set backlight in binary (on/off) form

    This function sets state of backlight pin.
 */
void BinaryBacklight::SetOn(
    bool on               /*!< Backlight state in on/off format */
) {
    digitalWrite(m_LEDPin, on? HIGH: LOW);
}

/*! \brief Set backlight brightness if supported

    This function enables binary backlight if brightness is non-zero.
 */
void BinaryBacklight::SetBrightness(
    uint8_t brightness    /*!< Backlight brightness value */
) {
    SetOn(brightness > 0? true: false);
}

/*! \brief Set backlight RGB colors if supported

    This function enables binary backlight if RGB is non-zero.
 */
void BinaryBacklight::SetRGB(
    uint8_t red,          /*!< Red color value */
    uint8_t green,        /*!< Green color value */
    uint8_t blue          /*!< Blue color value */
) {
    SetOn(red > 0 || green > 0 || blue > 0? true: false);
}
