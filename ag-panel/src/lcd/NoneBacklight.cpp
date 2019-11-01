/*!
  \file NoneBacklight.cpp
  \brief AG-Panel Project none backlight implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "NoneBacklight.h"

bool NoneBacklight::Init() {
  return true;
}

void NoneBacklight::Exit() {
}

void NoneBacklight::SetOn(bool on) {
  on = on;
}

void NoneBacklight::SetBrightness(uint8_t brightness) {
  brightness = brightness;
}

void NoneBacklight::SetRGB(uint8_t red, uint8_t green, uint8_t blue) {
  red = red;
  green = green;
  blue = blue;
}
