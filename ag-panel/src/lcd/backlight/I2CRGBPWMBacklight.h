/** @file I2CRGBPWMBacklight.h
    @brief AG-Panel Project I2C RGB PWM (0-255) backlight interface
    @copyright (C) 2020-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../../private.h"
#include "AbstractBacklight.h"

const uint32_t DefaultI2CRGBPWMBacklightDefaultColor = DefaultBacklightRGBColor;   /**< Default RGB PWM backlight color if not specified */
const uint8_t DefaultI2CRGBPWMBacklightScaleBrightness = MaxBacklightBrightness;   /**< Default RGB PWM backlight brightness if not specified */

/** @brief I2C RGB PWM Backlight class

    This class implements RGB PWM backlight based on PCA9633, 4-chan 8-bit PWM LED driver.
 */
class I2CRGBPWMBacklight: public AbstractBacklight {

public:
    explicit I2CRGBPWMBacklight(
        uint8_t RedChannel,       /**< Red LED digital channel */
        uint8_t GreenChannel,     /**< Green LED digital channel */
        uint8_t BlueChannel,      /**< Blue LED digital channel */
        uint8_t I2CAddress,       /**< I2C address of PWM LED driver chip */
        uint32_t DefaultColor = DefaultI2CRGBPWMBacklightDefaultColor,     /**< Default color if not specified */
        uint8_t ScaleBrightness = DefaultI2CRGBPWMBacklightScaleBrightness /**< Brightness scaling (dimming) value */
    ): AbstractBacklight(),
        m_RedChannel(RedChannel),
        m_GreenChannel(GreenChannel),
        m_BlueChannel(BlueChannel),
        m_I2CAddress(I2CAddress),
        m_DefaultColor(DefaultColor),
        m_ScaleBrightness(ScaleBrightness),
        m_Lowlevel(nullptr) { Init(); }
    virtual ~I2CRGBPWMBacklight() override { Exit(); }

    virtual void SetOn(bool on) override;
    virtual void SetBrightness(uint8_t brightness) override;
    virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override;
    using AbstractBacklight::SetRGB;

protected:
    uint8_t m_RedChannel;       /**< Red LED digital channel */
    uint8_t m_GreenChannel;     /**< Green LED digital channel */
    uint8_t m_BlueChannel;      /**< Blue LED digital channel */
    uint8_t m_I2CAddress;       /**< I2C address of PWM LED driver chip */
    uint32_t m_DefaultColor;    /**< Default color if not specified */
    uint8_t m_ScaleBrightness;  /**< Brightness scaling (dimming) value */

private:
    void *m_Lowlevel;       /**< Pointer to Low-Level LCD backlight class */
    bool Init();
    void Exit();
};
