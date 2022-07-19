/*! \file RGBPWMBacklight.h
    \brief AG-Panel Project RGB PWM (0-255) backlight interface
    \copyright (C) 2019-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../../private.h"
#include "AbstractBacklight.h"

const uint32_t DefaultRGBPWMBacklightDefaultColor = DefaultBacklightRGBColor;   /*!< Default RGB PWM backlight color if not specified */
const uint8_t DefaultRGBPWMBacklightScaleBrightness = MaxBacklightBrightness;   /*!< Default RGB PWM backlight brightness if not specified */

/*! \brief RGB PWM Backlight class

    This class implements RGB PWM backlight based on a 3 digital pin, one per LED color.
 */
class RGBPWMBacklight: public AbstractBacklight {

public:
    explicit RGBPWMBacklight(
        uint8_t RedPin,         /*!< Red LED digital pin */
        uint8_t GreenPin,       /*!< Green LED digital pin */
        uint8_t BluePin,        /*!< Blue LED digital pin */
        uint32_t DefaultColor = DefaultRGBPWMBacklightDefaultColor,     /*!< Default color if not specified */
        uint8_t ScaleBrightness = DefaultRGBPWMBacklightScaleBrightness /*!< Brightness scaling (dimming) value */
    ): AbstractBacklight(),
        m_RedPin(RedPin),
        m_GreenPin(GreenPin),
        m_BluePin(BluePin),
        m_DefaultColor(DefaultColor),
        m_ScaleBrightness(ScaleBrightness) { Init(); }
    virtual ~RGBPWMBacklight() override { Exit(); }

    virtual void SetOn(bool on) override;
    virtual void SetBrightness(uint8_t brightness) override;
    virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override;
    using AbstractBacklight::SetRGB;

protected:
    uint8_t m_RedPin;         /*!< Red LED digital pin */
    uint8_t m_GreenPin;       /*!< Green LED digital pin */
    uint8_t m_BluePin;        /*!< Blue LED digital pin */
    uint32_t m_DefaultColor;  /*!< Default color if not specified */
    uint8_t m_ScaleBrightness;  /*!< Brightness scaling (dimming) value */

private:
    bool Init();
    void Exit();
};
