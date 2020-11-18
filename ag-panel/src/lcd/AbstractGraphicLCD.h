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
    m_YOffset(0),
    m_CursorColumn(0),
    m_CursorRow(0) { Init(); }
  virtual ~AbstractGraphicLCD() override { Exit(); }

  using AbstractLCD::SetBacklight;
  using AbstractLCD::GetColumns;
  using AbstractLCD::GetRows;

  /*! \brief Clear graphic screen
  
    Inefficient but good-for-all implementation of graphic display clearing function.
    Presuposes the #SetPixel function implemented correctly.
    It's recommended to write optimized Clear functions in nested classes.
   */
  virtual void Clear() override {
    for(uint32_t y = 0; y < m_YSize; y++)
      for(uint32_t x = 0; x < m_XSize; x++)
        SetPixel(x, y, false);
  }

  /*! \brief Set text cursor to give position 

    Set position of text cursor.
   */
  virtual void SetCursor(
    uint8_t column,       /*!< New X-position of text cursor */
    uint8_t row           /*!< New Y-position of text cursor */
  ) override {
    if(column < m_Columns && row < m_Rows) {
      m_CursorColumn = column;
      m_CursorRow = row;
    }
  }

  /*! \brief Print a character
  
    Print a character from given font on graphic display and move cursor one step forward.
   */
  virtual void Print(
    char ch               /*!< Character to be printed */
  ) override {
    /* TODO */
  };

  /*! \brief Print a string
  
    Print a string of characters from given font on graphic display and move cursor each time one step forward.
    This function uses character-based #Print function internally.
   */
  virtual void Print(
    const char *str       /*!< String of characters to be printed */
  ) override {
    for(char ch = *str; ch != '\0'; str++) {
        Print(ch);
    }
  };

  virtual void SetPixel(uint16_t x, uint16_t y, bool on) = 0;

  /*! \brief Flush graphic display output

    Used to force flush buffered display output to graphic display.
    Override only if #SetPixel function implements some buffering and other optimizations.
   */
  virtual void Flush() {}

protected:
  AbstractFont *m_Font;       /*!< Pointer to a font instance */
  uint16_t m_XSize;           /*!< Number of pixels in X direction of the graphic LCD */
  uint16_t m_YSize;           /*!< Number of pixels in Y direction of the graphic LCD */
  uint16_t m_XOffset;         /*!< Number of pixels in X direction around text area of the graphic LCD */
  uint16_t m_YOffset;         /*!< Number of pixels in Y direction around text area of the graphic LCD */
  uint8_t m_CursorColumn;     /*!< X position of text cursor */
  uint8_t m_CursorRow;        /*!< Y position of text cursor */

  /*! \brief Count number of character positions based on font parameters
   */
  virtual void CalculateTextSize() {

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
