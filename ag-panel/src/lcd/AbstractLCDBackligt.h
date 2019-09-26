/*!
  \file AbstractLCDBackligt.h
  \brief AG-Panel Project abstract LCD backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"

inline uint32_t RGBColor2Uint(uint8_t red, uint8_t green, uint8_t blue) {
  return (uint32_t(red) & 0xFF) << 0 | (uint32_t(green) & 0xFF) << 8 | (uint32_t(blue) & 0xFF) << 16;
}

inline uint8_t RGBUint2Red(uint32_t uint) {
  return (uint >> 0) & 0xFF;
}

inline uint8_t RGBUint2Green(uint32_t uint) {
  return (uint >> 8) & 0xFF;
}

inline uint8_t RGBUint2Blue(uint32_t uint) {
  return (uint >> 16) & 0xFF;
}

const uint8_t DefaultLCDBacklightBrightness = 255;
const uint32_t DefaultLCDBacklightRGB = RGBColor2Uint(0, 0, 255);

class AbstractLCDBackligt {

public:
  AbstractLCDBackligt() { Init(); }
  virtual ~AbstractLCDBackligt() { Exit(); }

  virtual void SetBacklight(bool on) = 0;
  virtual void SetBacklight(uint8_t brightness) = 0;
  virtual void SetBacklight(uint8_t red, uint8_t green, uint8_t blue) = 0;
  virtual void SetBacklight(uint32_t rgb) = 0;

protected:

private:
  bool Init() { return true; }
  void Exit() {}
};
