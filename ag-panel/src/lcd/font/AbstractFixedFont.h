/*!
  \file AbstractFixedFont.h
  \brief AG-Panel Project abstract fixed size font interface
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../../private.h"
#include "AbstractFont.h"

/*!
  \brief Abstract Fixed Font class

  This is a base class for all fixed size font implementations.
  It defines only a base interface of fixed font used by the rest of a project code.
 */
class AbstractFixedFont: public AbstractFont {

public:
  explicit AbstractFixedFont():
    AbstractFont(),
    m_GlyphXSize(0),
    m_GlyphYSize(0),
    m_GlyphData(nullptr),
    m_DataRangeBegin(0),
    m_DataRangeEnd(0),
    m_DefaultGlyph(0),
    m_Glyph() { Init(); }
  virtual ~AbstractFixedFont() { Exit(); }

  /*! Get normal X size of font glyphs in pixels */
  virtual uint8_t GetGlyphXSize(void) const override { return m_GlyphXSize; }
  /*! Get normal Y size of font glyphs in pixels */
  virtual uint8_t GetGlyphYSize(void) const override { return m_GlyphYSize; }

  /*! Get a glyph data from raw pixel data array addressed by glyph number
    \returns Glyph description record in case of success, \a nullptr in case of error
  */
  virtual const Glyph *GetGlyph(
    uint8_t number      /*!< Glyph number */
  ) override {

    if(m_GlyphData == nullptr)
      return nullptr;

    m_Glyph.m_GlyphXSize = m_GlyphXSize;
    m_Glyph.m_GlyphYSize = m_GlyphYSize;
    m_Glyph.m_LineWidth = (m_Glyph.m_GlyphXSize + 7) / 8;
    m_Glyph.m_NumberLines = m_Glyph.m_GlyphYSize;

    if(number < m_DataRangeBegin || number > m_DataRangeEnd)
      number = m_DefaultGlyph;

    m_Glyph.m_PixelBuffer = &m_GlyphData[(number - m_DataRangeBegin) * m_Glyph.m_LineWidth * m_Glyph.m_NumberLines];

    return &m_Glyph;
  }

protected:
  uint8_t m_GlyphXSize;       /*!< Size of a glyph in X direction */
  uint8_t m_GlyphYSize;       /*!< Size of a glyph in Y direction */
  uint8_t *m_GlyphData;       /*!< Pointer to an arry of glyph raw data */
  uint16_t m_DataRangeBegin;  /*!< Number of first glyph in data array */
  uint16_t m_DataRangeEnd;    /*!< Number of last glyph in data array */
  uint16_t m_DefaultGlyph;    /*!< Default 'missing' glyph number */
  Glyph m_Glyph;              /*!< Glyph data returned by #GetGlyph */

private:
  bool Init() { return true; }
  void Exit() {}
};
