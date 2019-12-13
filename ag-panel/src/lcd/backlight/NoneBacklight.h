/*!
  \file NoneBacklight.h
  \brief AG-Panel Project none backlight interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../../private.h"
#include "AbstractBacklight.h"

/*!
  \brief None (dummy) Backlight class

  This class implements none backlight.
 */
class NoneBacklight: public AbstractBacklight {

public:
  NoneBacklight(): AbstractBacklight() { Init(); }
  virtual ~NoneBacklight() override { Exit(); }

  virtual void SetOn(bool on) override;
  virtual void SetBrightness(uint8_t brightness) override;
  virtual void SetRGB(uint8_t red, uint8_t green, uint8_t blue) override;

protected:

private:
  bool Init();
  void Exit();
};
