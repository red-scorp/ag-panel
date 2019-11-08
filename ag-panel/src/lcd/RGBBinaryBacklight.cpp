/*!
  \file RGBBinaryBacklight.cpp
  \brief AG-Panel Project RGB binary (8 colors) backlight implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "RGBBinaryBacklight.h"

/*!
  \brief Initialization of RGB backlight
  Configures RGB backlight digital pins.
  \returns true
 */
bool RGBBinaryBacklight::Init() {
  pinMode(m_RedPin, OUTPUT);
  pinMode(m_GreenPin, OUTPUT);
  pinMode(m_BluePin, OUTPUT);
  return true;
}

/*!
  \brief Deinitialisation of RGB backlight class
 */
void RGBBinaryBacklight::Exit() {
}

/*!
  \brief Set backlight in binary (on/off) form
  This function sets default color of RGB backlight if enabled.
 */
void RGBBinaryBacklight::SetOn(
  bool on               /*!< Backlight state in on/off format */
) {
  SetRGB(on? m_DefaultColor: 0);
}

/*!
  \brief Set backlight brightness if supported
  This function sets default color of RGB backlight if brightness is non-zero.
 */
void RGBBinaryBacklight::SetBrightness(
  uint8_t brightness    /*!< Backlight brightness value */
) {
  SetRGB(brightness > 0? m_DefaultColor: 0);
}

/*!
  \brief Set backlight RGB colors if supported
  This function sets color pins based on brightness values.
 */
void RGBBinaryBacklight::SetRGB(
  uint8_t red,          /*!< Red color value */
  uint8_t green,        /*!< Green color value */
  uint8_t blue          /*!< Blue color value */
) {
  digitalWrite(m_RedPin, red > 0? HIGH: LOW);
  digitalWrite(m_GreenPin, green > 0? HIGH: LOW);
  digitalWrite(m_BluePin, blue > 0? HIGH: LOW);
}
