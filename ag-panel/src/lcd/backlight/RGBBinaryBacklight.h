/*!
  \file RGBBinaryBacklight.h
  \brief AG-Panel Project RGB binary (8 colors) backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../../private.h"
#include "AbstractBacklight.h"

const uint32_t DefaultRGBBinaryBacklightDefaultColor = DefaultBacklightRGBColor;  /*!< Default RGB backlight color if not specified */

/*!
  \brief RGB Binary (7 colors) Backlight class

  This class implements RGB binary backlight based on a 3 digital pin, one per LED color.
 */
class RGBBinaryBacklight: public AbstractBacklight {

public:
  RGBBinaryBacklight(
    uint8_t RedPin,         /*!< Red LED digital pin */
    uint8_t GreenPin,       /*!< Green LED digital pin */
    uint8_t BluePin,        /*!< Blue LED digital pin */
    uint32_t DefaultColor = DefaultRGBBinaryBacklightDefaultColor   /*!< Default color if not specified */
  ): AbstractBacklight(),
    m_RedPin(RedPin),
    m_GreenPin(GreenPin),
    m_BluePin(BluePin),
    m_DefaultColor(DefaultColor) { Init(); }
  virtual ~RGBBinaryBacklight() override { Exit(); }

  virtual void SetOn(bool on) override;
  virtual void SetBrightness(uint8_t brightness) override;
  virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override;
  using AbstractBacklight::SetRGB;

protected:
  uint8_t m_RedPin;         /*!< Red LED digital pin */
  uint8_t m_GreenPin;       /*!< Green LED digital pin */
  uint8_t m_BluePin;        /*!< Blue LED digital pin */
  uint32_t m_DefaultColor;  /*!< Default color if not specified */

private:
  bool Init();
  void Exit();
};
