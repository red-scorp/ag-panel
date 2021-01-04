/*!
  \file AbstractU8GraphicLCD.h
  \brief AG-Panel Project U8g2lib-based graphic LCD interface
  \copyright (C) 2020-2021 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractGraphicLCD.h"
#include "U8g2lib.h"

/*!
  \brief U8g2lib-based Graphic LCD class

  This is a base class for graphic LCDs supported by U8glib.
 */
class AbstractU8GraphicLCD: public AbstractGraphicLCD {

public:
  explicit AbstractU8GraphicLCD(
    AbstractBacklight *Backlight,   /*!< Pointer to a backlight instance */
    AbstractFont *Font,         /*!< Pointer to a font instance */
    U8G2 *U8g2                  /*!< Pointer to an U8g2lib instance */
  ): AbstractGraphicLCD(Backlight, Font, m_U8g2->getWidth(), m_U8g2->getHeight()),
    m_U8g2(U8g2) { Init(); }
  virtual ~AbstractU8GraphicLCD() override { Exit(); }

  using AbstractGraphicLCD::SetBacklight;
  using AbstractGraphicLCD::GetColumns;
  using AbstractGraphicLCD::GetRows;

  using AbstractGraphicLCD::SetCursor;
  using AbstractGraphicLCD::Print;

  virtual void Clear() override {
    m_U8g2->setDrawColor(0);
    m_U8g2->drawBox(0, 0, m_XSize, m_YSize);
  }

  virtual void SetPixel(uint16_t x, uint16_t y, bool on) override {
    m_U8g2->setDrawColor(on? 1: 0);
    m_U8g2->drawPixel(x, y);
  }

  virtual void Flush() override {
    m_U8g2->nextPage();
  }  

protected:
  U8G2 *m_U8g2;

private:
  bool Init() {
    m_U8g2->firstPage();
    return true;
  };
  void Exit() {}
};
