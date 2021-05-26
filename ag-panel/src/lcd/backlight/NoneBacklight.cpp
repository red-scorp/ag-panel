/*!
  \file NoneBacklight.cpp
  \brief AG-Panel Project none backlight implementation
  \copyright (C) 2019-2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../../private.h"
#include "NoneBacklight.h"

/*!
  \brief Initialization of none backlight

  \returns true
 */
bool NoneBacklight::Init() {
  return true;
}

/*!
  \brief Deinitialization of none backlight class
 */
void NoneBacklight::Exit() {
}

/*!
  \brief Set backlight in binary (on/off) form
 */
void NoneBacklight::SetOn(
  bool on               /*!< Backlight state in on/off format */
) {
  on = on;
}

/*!
  \brief Set backlight brightness if supported
 */
void NoneBacklight::SetBrightness(
  uint8_t brightness    /*!< Backlight brightness value */
) {
  brightness = brightness;
}

/*!
  \brief Set backlight RGB colors if supported
 */
void NoneBacklight::SetRGB(
  uint8_t red,          /*!< Red color value */
  uint8_t green,        /*!< Green color value */
  uint8_t blue          /*!< Blue color value */
) {
  red = red;
  green = green;
  blue = blue;
}
