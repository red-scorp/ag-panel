/*!
  \file AbstractBacklight.h
  \brief AG-Panel Project abstract backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"

constexpr inline uint32_t RGBColor2Uint(uint8_t red, uint8_t green, uint8_t blue) {
  return (uint32_t(red) & 0xFF) << 0 | (uint32_t(green) & 0xFF) << 8 | (uint32_t(blue) & 0xFF) << 16;
}

constexpr inline uint8_t RGBUint2Red(uint32_t uint) {
  return (uint >> 0) & 0xFF;
}

constexpr inline uint8_t RGBUint2Green(uint32_t uint) {
  return (uint >> 8) & 0xFF;
}

constexpr inline uint8_t RGBUint2Blue(uint32_t uint) {
  return (uint >> 16) & 0xFF;
}

constexpr inline uint8_t ScaleColor(uint8_t color, uint8_t max) {
  return (uint16_t(color) * (max + 1)) >> 8;
}

constexpr inline uint32_t ScaleRGB(uint32_t rgb, uint8_t max) {
  return RGBColor2Uint(ScaleColor(RGBUint2Red(rgb), max), ScaleColor(RGBUint2Green(rgb), max), ScaleColor(RGBUint2Blue(rgb), max));
}

const uint8_t MaxBacklightBrightness = 255;
const uint8_t DefaultBacklightBrightness = MaxBacklightBrightness;
const uint32_t DefaultBacklightRGBColor = RGBColor2Uint(0, 0, MaxBacklightBrightness);

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
