/*!
  \file AbstractU8GraphicLCD.h
  \brief AG-Panel Project U8glib-based graphic LCD interface
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractGraphicLCD.h"
#include "U8glib.h"

/*!
  \brief U8glib-based Graphic LCD class

  This is a base class for graphic LCDs supported by U8glib.
 */
class AbstractU8GraphicLCD: public AbstractGraphicLCD {

public:
  explicit AbstractU8GraphicLCD(
    AbstractBacklight *Backlight,   /*!< Pointer to a backlight instance */
    AbstractFont *Font,         /*!< Pointer to a font instance */
    U8GLIB *U8g                 /*!< Pointer to an U8glib instance */
  ): AbstractGraphicLCD(Backlight, Font, m_U8g->getWidth(), m_U8g->getHeight()),
    m_U8g(U8g) { Init(); }
  virtual ~AbstractU8GraphicLCD() override { Exit(); }

  using AbstractGraphicLCD::SetBacklight;
  using AbstractGraphicLCD::GetColumns;
  using AbstractGraphicLCD::GetRows;

  using AbstractGraphicLCD::SetCursor;
  using AbstractGraphicLCD::Print;

  virtual void Clear() override {
    m_U8g->setDefaultBackgroundColor();
    m_U8g->drawBox(0, 0, m_XSize, m_YSize);
  }

  virtual void SetPixel(uint16_t x, uint16_t y, bool on) override {
    if ( m_U8g->getMode() == U8G_MODE_HICOLOR ) {
      uint8_t c = on? 255: 0;
      m_U8g->setHiColorByRGB(c, c, c);
    } else {
      m_U8g->setColorIndex(on? 1: 0);
    }
    m_U8g->drawPixel(x, y);
  }

  virtual void Flush() override {
    m_U8g->nextPage();
  }  

protected:
  U8GLIB *m_U8g;

private:
  bool Init() {
    m_U8g->firstPage();
    return true;
  };
  void Exit() {}
};
