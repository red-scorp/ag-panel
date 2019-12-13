/*!
  \file AbstractLCD.h
  \brief AG-Panel Project abstract LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "backlight/AbstractBacklight.h"

/*!
  \brief Abstract LCD class

  This is a base class for all LCD implementations.
  It defines only a base interface of LCD used by the rest of a project code.
 */
class AbstractLCD {

public:
  AbstractLCD(
    AbstractBacklight *Backlight,  /*!< Pointer to a backlight instance */
    uint8_t Columns,            /*!< Number of columns of the text LCD */
    uint8_t Rows                /*!< Number of rows of the text LCD */
  ): m_Backlight(Backlight),
    m_Columns(Columns),
    m_Rows(Rows) { Init(); }
  virtual ~AbstractLCD() { Exit(); }

  /*! Set backlight in binary (on/off) form */
  virtual void SetBacklight(
    bool on               /*!< Backlight state in on/off format */
  ) { m_Backlight->SetOn(on); }
  /*! Set backlight brightness if supported */
  virtual void SetBacklight(
    uint8_t brightness    /*!< Backlight brightness value */
  ) { m_Backlight->SetBrightness(brightness); }
  /*! Set backlight RGB colors if supported */
  virtual void SetBacklight(
    uint8_t red,          /*!< Red color value */
    uint8_t green,        /*!< Green color value */
    uint8_t blue          /*!< Blue color value */
  ) { m_Backlight->SetRGB(red, green, blue); }
  /*! Set backlight RGB colors if supported */
  virtual void SetBacklight(
    uint32_t rgb          /*!< RGB integer value */
  ) { m_Backlight->SetRGB(rgb); }

  virtual void Clear() = 0;
  virtual void SetCursor(uint8_t column, uint8_t row) = 0;
  virtual void Print(const char *str) = 0;

  virtual uint8_t GetColumns() const { return m_Columns; }
  virtual uint8_t GetRows() const { return m_Rows; }

protected:
  AbstractBacklight *m_Backlight;     /*!< Pointer to a backlight instance */
  uint8_t m_Columns;            /*!< Number of columns of the text LCD */
  uint8_t m_Rows;               /*!< Number of rows of the text LCD */

private:
  bool Init() { return true; }
  void Exit() {}
};
