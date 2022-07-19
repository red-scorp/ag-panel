/*! \file Fixed8x8TestFont.h
    \brief AG-Panel Project fixed size 8x8 test font interface
    \copyright (C) 2020-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../../private.h"
#include "AbstractFixedFont.h"

/*! \brief Fixed 8x8 Test Font class

    This is a test font with a single character of 8x8 pixel big to test graphic displays output.
 */
class Fixed8x8TestFont: public AbstractFixedFont {

public:
    explicit Fixed8x8TestFont():
        AbstractFixedFont() { Init(); }
    virtual ~Fixed8x8TestFont() { Exit(); }

    using AbstractFixedFont::GetGlyphXSize;
    using AbstractFixedFont::GetGlyphYSize;
    using AbstractFixedFont::GetGlyph;

protected:

private:
    bool Init();
    void Exit();
};
