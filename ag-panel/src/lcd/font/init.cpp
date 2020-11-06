/*!
  \file init.cpp
  \brief AG-Panel Project LCD font initialization
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#include "../../private.h"
#include "../../../config.h"

#include "all.h"

/*!
  \brief Initialize LCD font

  This function chooses one of font classes to use based on configuration defined in config.h
  \returns Pointer to LCD font class
 */
AbstractFont *initFont() {
  AbstractFont *p_Font = nullptr;

  #if defined(LCD_FONT_8X8_TEST)
    // TODO: add code here!
  #endif

  return p_Font;
}