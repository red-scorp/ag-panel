/** @file PWMBacklight.cpp
    @brief AG-Panel Project PWM (0-255) backlight implementation
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../../private.h"
#include "PWMBacklight.h"

/** @brief Initialization of PWM backlight

    Configures binary backlight digital pin.
    @returns true
 */
bool PWMBacklight::Init() {
    pinMode(m_LEDPin, OUTPUT);
    return true;
}

/** @brief Deinitialization of PWM backlight class
 */
void PWMBacklight::Exit() {
}

/** @brief Set backlight in binary (on/off) form

    This function sets maximum brightness of PWM backlight if enabled.
 */
void PWMBacklight::SetOn(
    bool on               /**< Backlight state in on/off format */
) {
    SetBrightness(on? MaxBacklightBrightness: 0);
}

/** @brief Set backlight brightness if supported

    This function writes brightness value to PWM pin.
 */
void PWMBacklight::SetBrightness(
    uint8_t brightness    /**< Backlight brightness value */
) {
    analogWrite(m_LEDPin, ScaleColor(brightness, m_ScaleBrightness));
}

/** @brief Set backlight RGB colors if supported

    This function sets PWM backlight brightness based on RGB value.
 */
void PWMBacklight::SetRGB(
    uint8_t red,          /**< Red color value */
    uint8_t green,        /**< Green color value */
    uint8_t blue          /**< Blue color value */
) {
    SetBrightness((red + green + blue) / 3);
}
