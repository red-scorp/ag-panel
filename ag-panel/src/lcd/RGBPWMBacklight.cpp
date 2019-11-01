/*!
  \file RGBPWMBacklight.cpp
  \brief AG-Panel Project RGB PWM (0-255) backlight implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "RGBPWMBacklight.h"

bool RGBPWMBacklight::Init() {
  pinMode(m_RedPin, OUTPUT);
  pinMode(m_GreenPin, OUTPUT);
  pinMode(m_BluePin, OUTPUT);
  return true;
}

void RGBPWMBacklight::Exit() {
}

void RGBPWMBacklight::SetOn(bool on) {
  SetBrightness(on? MaxBacklightBrightness: 0);
}

void RGBPWMBacklight::SetBrightness(uint8_t brightness) {
  SetRGB(ScaleRGB(m_DefaultColor, brightness));
}

void RGBPWMBacklight::SetRGB(uint8_t red, uint8_t green, uint8_t blue) {
  analogWrite(m_RedPin, ScaleColor(red, m_ScaleBrightness));
  analogWrite(m_GreenPin, ScaleColor(green, m_ScaleBrightness));
  analogWrite(m_BluePin, ScaleColor(blue, m_ScaleBrightness));
}
