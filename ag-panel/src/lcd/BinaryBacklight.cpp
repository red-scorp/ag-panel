/*!
  \file BinaryBacklight.cpp
  \brief AG-Panel Project binary (on/off) backlight implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "BinaryBacklight.h"

bool BinaryBacklight::Init() {
  pinMode(m_LEDPin, OUTPUT);
  return true;
}

void BinaryBacklight::Exit() {
}

void BinaryBacklight::SetOn(bool on) {
  digitalWrite(m_LEDPin, on? HIGH: LOW);
}

void BinaryBacklight::SetBrightness(uint8_t brightness) {
  SetOn(brightness > 0? true: false);
}

void BinaryBacklight::SetRGB(uint8_t red, uint8_t green, uint8_t blue) {
  SetOn(red > 0 || green > 0 || blue > 0? true: false);
}
