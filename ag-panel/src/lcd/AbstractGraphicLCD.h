/*!
  \file AbstractGraphicLCD.h
  \brief AG-Panel Project abstract graphic LCD interface
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractLCD.h"
#include "font/AbstractFont.h"

/*!
  \brief Abstract Graphic LCD class

  This is a base class for all graphic LCD implementations.
  It defines only a base interface of graphic LCD used by the rest of a project code.
 */
class AbstractGraphicLCD: public AbstractLCD {

public:
  explicit AbstractGraphicLCD(
    AbstractBacklight *Backlight,   /*!< Pointer to a backlight instance */
    AbstractFont *Font,         /*!< Pointer to a font instance */
    uint16_t XSize,             /*!< Number of pixels in X direction of the graphic LCD */
    uint16_t YSize              /*!< Number of pixels in Y direction of the graphic LCD */
  ): AbstractLCD(Backlight, 0, 0),
    m_Font(Font),
    m_XSize(XSize),
    m_YSize(YSize),
    m_XOffset(0),
    m_YOffset(0) { Init(); }
  virtual ~AbstractGraphicLCD() override { Exit(); }

  using AbstractLCD::SetBacklight;
  using AbstractLCD::Clear;
  using AbstractLCD::SetCursor;
  using AbstractLCD::Print;
  using AbstractLCD::GetColumns;
  using AbstractLCD::GetRows;

  virtual void SetPixel(uint16_t x, uint16_t y, bool on) = 0;
  virtual void Flush() {}

protected:
  AbstractFont *m_Font;       /*!< Pointer to a font instance */
  uint16_t m_XSize;           /*!< Number of pixels in X direction of the graphic LCD */
  uint16_t m_YSize;           /*!< Number of pixels in Y direction of the graphic LCD */
  uint16_t m_XOffset;         /*!< Number of pixels in X direction around text area of the graphic LCD */
  uint16_t m_YOffset;         /*!< Number of pixels in Y direction around text area of the graphic LCD */

  /*! \brief Count number of character positions based on font parameters
   */
  void CalculateTextSize() {

    if(m_Font != nullptr) { /* do we have font instance? */
      if(m_Font->GetGlyphXSize() != 0) { /* do we have font with fixed X size? */
        m_Columns = m_XSize / m_Font->GetGlyphXSize();
        m_XOffset = (m_XSize % m_Font->GetGlyphXSize()) / 2;
      }
      if(m_Font->GetGlyphYSize() != 0) { /* do we have font with fixed Y size? */
        m_Rows = m_YSize / m_Font->GetGlyphYSize();
        m_YOffset = (m_YSize % m_Font->GetGlyphXSize()) / 2;
      }
    }
  }

private:
  bool Init() { CalculateTextSize(); return true; }
  void Exit() {}
};
