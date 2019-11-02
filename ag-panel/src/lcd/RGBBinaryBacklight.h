/*!
  \file RGBBinaryBacklight.h
  \brief AG-Panel Project RGB binary (8 colors) backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractBacklight.h"

const uint32_t DefaultRGBBinaryBacklightDefaultColor = DefaultBacklightRGBColor;

class RGBBinaryBacklight: public AbstractBacklight {

public:
  RGBBinaryBacklight(uint8_t RedPin, uint8_t GreenPin, uint8_t BluePin, uint32_t DefaultColor = DefaultRGBBinaryBacklightDefaultColor): AbstractBacklight(), m_RedPin(RedPin), m_GreenPin(GreenPin), m_BluePin(BluePin), m_DefaultColor(DefaultColor) { Init(); }
  virtual ~RGBBinaryBacklight() override { Exit(); }

  virtual void SetOn(bool on) override;
  virtual void SetBrightness(uint8_t brightness) override;
  virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override;
  using AbstractBacklight::SetRGB;

protected:
  uint8_t m_RedPin;
  uint8_t m_GreenPin;
  uint8_t m_BluePin;
  uint32_t m_DefaultColor;

private:
  bool Init();
  void Exit();
};
