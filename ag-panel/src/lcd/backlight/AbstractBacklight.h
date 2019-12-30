/*!
  \file AbstractBacklight.h
  \brief AG-Panel Project abstract backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../../private.h"

/*!
  \brief Convert 3 RGB color components in to a single integer value

  \returns Integer value for RGB
 */
constexpr inline uint32_t RGBColor2Uint(
  uint8_t red,      /*!< Brightness of red color */
  uint8_t green,    /*!< Brightness of green color */
  uint8_t blue      /*!< Brightness of blue color */
) {
  return (uint32_t(red) & 0xFF) << 0 | (uint32_t(green) & 0xFF) << 8 | (uint32_t(blue) & 0xFF) << 16;
}

/*!
  \brief Extract red component from integer RGB value

  \returns Brightness of red color
 */
constexpr inline uint8_t RGBUint2Red(
  uint32_t rgb      /*!< Integer RGB value */
) {
  return (rgb >> 0) & 0xFF;
}

/*!
  \brief Extract green component from integer RGB value

  \returns Brightness of green color
 */
constexpr inline uint8_t RGBUint2Green(
  uint32_t rgb      /*!< Integer RGB value */
) {
  return (rgb >> 8) & 0xFF;
}

/*!
  \brief Extract blue component from integer RGB value

  \returns Brightness of blue color
 */
constexpr inline uint8_t RGBUint2Blue(
  uint32_t rgb      /*!< Integer RGB value */
) {
  return (rgb >> 16) & 0xFF;
}

/*!
  /brief Scale a brightness value relative to maximum value

  /returns Scaled color/brightness value
 */
constexpr inline uint8_t ScaleColor(
  uint8_t color,    /*!< Initial color/brightness value */
  uint8_t max       /*!< Maximum value for scaling */
) {
  return ((uint16_t(color) * uint16_t(max + 1)) >> 8) & 0xFF;
}

/*!
  /brief Scale an RGB value relative to maximum value

  /returns Scaled RGB value
 */
constexpr inline uint32_t ScaleRGB(
  uint32_t rgb,     /*!< Initial RGB value */
  uint8_t max       /*!< Maximum value for scaling */
) {
  return RGBColor2Uint(ScaleColor(RGBUint2Red(rgb), max), ScaleColor(RGBUint2Green(rgb), max), ScaleColor(RGBUint2Blue(rgb), max));
}

const uint8_t MaxBacklightBrightness = 255;     /*!< Maximum value of brightness for backlight */
const uint8_t DefaultBacklightBrightness = MaxBacklightBrightness;    /*!< Default brightness of backlight if enabled without specifics */
const uint32_t DefaultBacklightRGBColor = RGBColor2Uint(0, 0, MaxBacklightBrightness);    /*!< Default color of backlight if set without specifics */

/*!
  \brief Abstract Backlight class

  This is a base class for all backlight implementations.
  It defines only a base interface of backlight used by the rest of a project code.
 */
class AbstractBacklight {

public:
  AbstractBacklight() { Init(); }
  virtual ~AbstractBacklight() { Exit(); }

  virtual void SetOn(bool on) = 0;
  virtual void SetBrightness(uint8_t brightness) = 0;
  virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) = 0;
  virtual void SetRGB(uint32_t rgb) { SetRGB(RGBUint2Red(rgb), RGBUint2Green(rgb), RGBUint2Blue(rgb)); };

protected:

private:
  bool Init() { return true; }
  void Exit() {}
};
