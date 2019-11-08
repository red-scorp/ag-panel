/*!
  \file RGBPWMBacklight.cpp
  \brief AG-Panel Project RGB PWM (0-255) backlight implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "RGBPWMBacklight.h"

/*!
  \brief Initialization of RGB PWM backlight
  Configures RGB backlight digital pins.
  \returns true
 */
bool RGBPWMBacklight::Init() {
  pinMode(m_RedPin, OUTPUT);
  pinMode(m_GreenPin, OUTPUT);
  pinMode(m_BluePin, OUTPUT);
  return true;
}

/*!
  \brief Deinitialisation of RGB PWM backlight class
 */
void RGBPWMBacklight::Exit() {
}

/*!
  \brief Set backlight in binary (on/off) form
  This function sets maximu brightness of RGB PWM backlight if enabled.
 */
void RGBPWMBacklight::SetOn(
  bool on               /*!< Backlight state in on/off format */
) {
  SetBrightness(on? MaxBacklightBrightness: 0);
}

/*!
  \brief Set backlight brightness if supported
  This function sets default color of RGB backlight scaled to specified brightness.
 */
void RGBPWMBacklight::SetBrightness(
  uint8_t brightness    /*!< Backlight brightness value */
) {
  SetRGB(ScaleRGB(m_DefaultColor, brightness));
}

/*!
  \brief Set backlight RGB colors if supported
  This function sets PWM color value to digital pins based on brightness values.
 */
void RGBPWMBacklight::SetRGB(
  uint8_t red,          /*!< Red color value */
  uint8_t green,        /*!< Green color value */
  uint8_t blue          /*!< Blue color value */
) {
  analogWrite(m_RedPin, ScaleColor(red, m_ScaleBrightness));
  analogWrite(m_GreenPin, ScaleColor(green, m_ScaleBrightness));
  analogWrite(m_BluePin, ScaleColor(blue, m_ScaleBrightness));
}
