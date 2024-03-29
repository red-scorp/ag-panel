/** @file I2CRGBPWMBacklight.cpp
    @brief AG-Panel Project I2C RGB PWM (0-255) backlight implementation
    @copyright (C) 2020-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../../private.h"
#include "I2CRGBPWMBacklight.h"

#if !defined(ARDUINO_ARCH_GD32V) && !defined(ARDUINO_ARCH_KENDRYTE)

#include <pca9633.h>
#include <Wire.h>

/** @brief Initialization of I2C RGB PWM backlight

    Configures I2C LED controller to work as RGB backlight.
    @returns true
 */
bool I2CRGBPWMBacklight::Init() {
    Wire.begin();
    m_Lowlevel = new PCA9633;
    PCA9633 *p_I2CBacklight = reinterpret_cast<PCA9633*>(m_Lowlevel);
    p_I2CBacklight->begin(m_I2CAddress);
    return true;
}

/** @brief Deinitialization of I2C RGB PWM backlight class
 */
void I2CRGBPWMBacklight::Exit() {
    PCA9633 *p_I2CBacklight = reinterpret_cast<PCA9633*>(m_Lowlevel);
    if(p_I2CBacklight != nullptr)
        delete p_I2CBacklight;
    m_Lowlevel = nullptr;
}

/** @brief Set backlight in binary (on/off) form

    This function sets maximum brightness of RGB PWM backlight if enabled.
 */
void I2CRGBPWMBacklight::SetOn(
    bool on               /**< Backlight state in on/off format */
) {
    SetBrightness(on? MaxBacklightBrightness: 0);
}

/** @brief Set backlight brightness if supported

    This function sets default color of RGB backlight scaled to specified brightness.
 */
void I2CRGBPWMBacklight::SetBrightness(
    uint8_t brightness    /**< Backlight brightness value */
) {
    SetRGB(ScaleRGB(m_DefaultColor, brightness));
}

/** @brief Set backlight RGB colors if supported

    This function sets PWM color value to LED drivers channels based on brightness values.
 */
void I2CRGBPWMBacklight::SetRGB(
    uint8_t red,          /**< Red color value */
    uint8_t green,        /**< Green color value */
    uint8_t blue          /**< Blue color value */
) {
    PCA9633 *p_I2CBacklight = reinterpret_cast<PCA9633*>(m_Lowlevel);
    p_I2CBacklight->setpwm(m_RedChannel, MaxBacklightBrightness - ScaleColor(red, m_ScaleBrightness));
    p_I2CBacklight->setpwm(m_GreenChannel, MaxBacklightBrightness - ScaleColor(green, m_ScaleBrightness));
    p_I2CBacklight->setpwm(m_BlueChannel, MaxBacklightBrightness - ScaleColor(blue, m_ScaleBrightness));
}

#else
#warning 'I2CRGBPWMBacklight' is not implemented for GD32V and KENDRYTE platforms because it lacks of standard header 'Wire.h'!
#endif /* !ARDUINO_ARCH_GD32V */
