/*!
  \file PWMBacklight.h
  \brief AG-Panel Project PWM (0-255) backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractBacklight.h"

const uint8_t DefaultPWMBacklightScaleBrightness = MaxBacklightBrightness;  /*!< Default PWM backlight brightness if not specified */

/*!
  \brief PWM Backlight class
  This class implements PWM backlight based on a single digital pin.
 */
class PWMBacklight: public AbstractBacklight {

public:
  PWMBacklight(
    uint8_t LEDPin,     /*!< PWM backlight digital pin */
    uint8_t ScaleBrightness = DefaultPWMBacklightScaleBrightness  /*!< Brightness scaling (dimming) value */
  ): AbstractBacklight(), m_LEDPin(LEDPin), m_ScaleBrightness(ScaleBrightness) { Init(); }
  virtual ~PWMBacklight() override { Exit(); }

  virtual void SetOn(bool on) override;
  virtual void SetBrightness(uint8_t brightness) override;
  virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override;

protected:
  uint8_t m_LEDPin;     /*!< PWM backlight digital pin */
  uint8_t m_ScaleBrightness;  /*!< Brightness scaling (dimming) value */

private:
  bool Init();
  void Exit();
};
