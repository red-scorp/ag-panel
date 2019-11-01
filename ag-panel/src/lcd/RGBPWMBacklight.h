/*!
  \file RGBPWMBacklight.h
  \brief AG-Panel Project RGB PWM (0-255) backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractBacklight.h"

const uint32_t DefaultRGBPWMBacklightDefaultColor = DefaultBacklightRGBColor;
const uint8_t DefaultRGBPWMBacklightScaleBrightness = MaxBacklightBrightness;

class RGBPWMBacklight: public AbstractBacklight {

public:
  RGBPWMBacklight(uint8_t RedPin, uint8_t GreenPin, uint8_t BluePin, uint32_t DefaultColor = DefaultRGBPWMBacklightDefaultColor, uint8_t ScaleBrightness = DefaultRGBPWMBacklightScaleBrightness): AbstractBacklight(), m_RedPin(RedPin), m_GreenPin(GreenPin), m_BluePin(BluePin), m_DefaultColor(DefaultColor), m_ScaleBrightness(ScaleBrightness) { Init(); }
  virtual ~RGBPWMBacklight() { Exit(); }

  virtual void SetOn(bool on) override;
  virtual void SetBrightness(uint8_t brightness) override;
  virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override;
  using AbstractBacklight::SetRGB;

protected:
  uint8_t m_RedPin;
  uint8_t m_GreenPin;
  uint8_t m_BluePin;
  uint32_t m_DefaultColor;
  uint8_t m_ScaleBrightness;

private:
  bool Init();
  void Exit();
};
