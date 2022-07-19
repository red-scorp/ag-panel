/*! \file Fixed8x8TestFont.cpp
    \brief AG-Panel Project fixed size 8x8 test font implementation
    \copyright (C) 2020-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../../private.h"
#include "Fixed8x8TestFont.h"

/*!
    \brief 8x8 test font data.

    This array defines two characters:
    - 31 a placeholder (a crossed box)
    - 32 a space (empty)
*/
static uint8_t s_8x8TestFontData[] = {
    // Symbol 31 - [x] (placeholder)
    0b11111110,
    0b11000110,
    0b10101010,
    0b10010010,
    0b10101010,
    0b11000110,
    0b11111110,
    0b00000000,
    // Symbol 32 - Space
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};

/*! \brief Initialization of 8x8 test font

    Initializes internal parameters of the font.
    \returns true
 */
bool Fixed8x8TestFont::Init() {

    m_GlyphXSize = 8;
    m_GlyphYSize = 8;
    m_GlyphData = s_8x8TestFontData;
    m_DataRangeBegin = 31;
    m_DataRangeEnd = 32;
    m_DefaultGlyph = 31;

    return true;
}

/*! \brief Deinitialization of 8x8 test font
 */
void Fixed8x8TestFont::Exit() {
}
