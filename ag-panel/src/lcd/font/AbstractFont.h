/*! \file AbstractFont.h
    \brief AG-Panel Project abstract font interface
    \copyright (C) 2020-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../../private.h"

/*! \brief Glyph Descriptor

    This is a glyph format which will be returned by function #GetGlyph.
 */
class Glyph {

public:
    Glyph():
        m_GlyphXSize(0),
        m_GlyphYSize(0),
        m_LineWidth(0),
        m_NumberLines(0),
        m_PixelBuffer(nullptr) {}

public:
    uint8_t m_GlyphXSize;     /*!< Size of the glyph in X direction in pixels */
    uint8_t m_GlyphYSize;     /*!< Size of the glyph in Y direction in pixels */
    uint8_t m_LineWidth;      /*!< Horizontal width of glyphs in bytes */
    uint8_t m_NumberLines;    /*!< Vertical number of lines in this glyph */
    const uint8_t *m_PixelBuffer;   /*!< Pointer to an array of bytes which holds glyph data */
};

/*! \brief Abstract Font class

    This is a base class for all font implementations.
    It defines only a base interface of font used by the rest of a project code.
 */
class AbstractFont {

public:
    explicit AbstractFont() { Init(); }
    virtual ~AbstractFont() { Exit(); }

    /*! Get normal X size of font glyphs in pixels */
    virtual uint8_t GetGlyphXSize(void) const { return 0; };
    /*! Get normal Y size of font glyphs in pixels */
    virtual uint8_t GetGlyphYSize(void) const { return 0; };

    virtual const Glyph *GetGlyph(uint8_t number) = 0;

protected:

private:
    bool Init() { return true; }
    void Exit() {}
};
