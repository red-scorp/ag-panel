/*!
  \file RGBBinaryBacklight.cpp
  \brief AG-Panel Project RGB binary (8 colors) backlight implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "RGBBinaryBacklight.h"

bool RGBBinaryBacklight::Init() {
  pinMode(m_RedPin, OUTPUT);
  pinMode(m_GreenPin, OUTPUT);
  pinMode(m_BluePin, OUTPUT);
  return true;
}

void RGBBinaryBacklight::Exit() {
}

void RGBBinaryBacklight::SetOn(bool on) {
  SetRGB(on? m_DefaultColor: 0);
}

void RGBBinaryBacklight::SetBrightness(uint8_t brightness) {
  SetRGB(brightness > 0? m_DefaultColor: 0);
}

void RGBBinaryBacklight::SetRGB(uint8_t red, uint8_t green, uint8_t blue) {
  digitalWrite(m_RedPin, red > 0? HIGH: LOW);
  digitalWrite(m_GreenPin, green > 0? HIGH: LOW);
  digitalWrite(m_BluePin, blue > 0? HIGH: LOW);
}
