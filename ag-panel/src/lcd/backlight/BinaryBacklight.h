/*!
  \file BinaryBacklight.h
  \brief AG-Panel Project binary (on/off) backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../../private.h"
#include "AbstractBacklight.h"

/*!
  \brief Binary (on/off) Backlight class

  This class implements binary backlight based on a single digital pin.
 */
class BinaryBacklight: public AbstractBacklight {

public:
  BinaryBacklight(
    uint8_t LEDPin      /*!< Binary backlight digital pin */
  ): AbstractBacklight(),
    m_LEDPin(LEDPin) { Init(); }
  virtual ~BinaryBacklight() override { Exit(); }

  virtual void SetOn(bool on) override;
  virtual void SetBrightness(uint8_t brightness) override;
  virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override;

protected:
  uint8_t m_LEDPin;     /*!< Binary backlight digital pin */

private:
  bool Init();
  void Exit();
};
