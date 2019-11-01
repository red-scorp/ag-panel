/*!
  \file PWMBacklight.cpp
  \brief AG-Panel Project PWM (0-255) backlight implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "PWMBacklight.h"

bool PWMBacklight::Init() {
  pinMode(m_LEDPin, OUTPUT);
  return true;
}

void PWMBacklight::Exit() {
}

void PWMBacklight::SetOn(bool on) {
  SetBrightness(on? MaxBacklightBrightness: 0);
}

void PWMBacklight::SetBrightness(uint8_t brightness) {
  analogWrite(m_LEDPin, ScaleColor(brightness, m_ScaleBrightness));
}

void PWMBacklight::SetRGB(uint8_t red, uint8_t green, uint8_t blue) {
  SetBrightness((red + green + blue) / 3);
}
