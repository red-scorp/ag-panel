/*!
  \file I2CTextLCD.cpp
  \brief AG-Panel Project I2C 4-bit text (hd44780) LCD implmentation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "I2CTextLCD.h"
#include <LiquidCrystal_I2C.h>

/*!
  \brief Initialization of I2C text LCD display

  Configures I2C text LCD display to work with specified geometry.
  \returns true
 */
bool I2CTextLCD::Init() {
  m_Lowlevel = new LiquidCrystal_I2C(m_I2CAddress, m_Columns, m_Rows);
  LiquidCrystal_I2C *p_I2CLCD = (LiquidCrystal_I2C*)m_Lowlevel;
  p_I2CLCD->init();
  return true;
}

/*!
  \brief Deinitialisation of I2C text LCD display class
 */
void I2CTextLCD::Exit() {
  LiquidCrystal_I2C *p_I2CLCD = (LiquidCrystal_I2C*)m_Lowlevel;
  if(p_I2CLCD != nullptr)
    delete p_I2CLCD;
  m_Lowlevel = nullptr;
}

/*!
  \brief Set backlight in binary (on/off) form

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CTextLCD::SetBacklight(
  bool on               /*!< Backlight state in on/off format */
) {
  LiquidCrystal_I2C *p_I2CLCD = (LiquidCrystal_I2C*)m_Lowlevel;
  if(on)
    p_I2CLCD->backlight();
  else
    p_I2CLCD->noBacklight();
}

/*!
  \brief Set backlight brightness if supported

  This function enables LCD backlight if brightness is non-zero.
 */
void I2CTextLCD::SetBacklight(
  uint8_t brightness    /*!< Backlight brightness value */
) {
  SetBacklight(bool(brightness > 0? true: false));
}

/*!
  \brief Set backlight RGB colors if supported

  This function enables LCD backlight if RGB is non-zero.
 */
void I2CTextLCD::SetBacklight(
  uint8_t red,          /*!< Red color value */
  uint8_t green,        /*!< Green color value */
  uint8_t blue          /*!< Blue color value */
) {
  SetBacklight(bool(red > 0 || green > 0 || blue > 0? true: false));
}

/*!
  \brief Set backlight RGB colors if supported

  This function enables LCD backlight if RGB is non-zero.
 */
void I2CTextLCD::SetBacklight(
  uint32_t rgb          /*!< RGB integer value */
) {
  SetBacklight(bool(rgb > 0? true: false));
}

/*!
  \brief Clear LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CTextLCD::Clear() {
  LiquidCrystal_I2C *p_I2CLCD = (LiquidCrystal_I2C*)m_Lowlevel;
  p_I2CLCD->clear();
}

/*!
  \brief Set Cursor on LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CTextLCD::SetCursor(
  uint8_t column,       /*!< Column to put the cursor to */
  uint8_t row           /*!< Row to put the cursor to */
) {
  LiquidCrystal_I2C *p_I2CLCD = (LiquidCrystal_I2C*)m_Lowlevel;
  p_I2CLCD->setCursor(column, row);
}

/*!
  \brief Print a text on LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CTextLCD::Print(
  const char *str       /*!< String to print */
) {
  LiquidCrystal_I2C *p_I2CLCD = (LiquidCrystal_I2C*)m_Lowlevel;
  p_I2CLCD->print(str);
}

/*!
  \brief Write a byte (RS = 1) to LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CTextLCD::Write(
  uint8_t byte          /* !< Byte to write to LCD display */
) {
  LiquidCrystal_I2C *p_I2CLCD = (LiquidCrystal_I2C*)m_Lowlevel;
  p_I2CLCD->write(byte);
}

/*!
  \brief Send a command byte (RS = 0) to LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CTextLCD::Command(
  uint8_t byte          /* !< Command to send to LCD display */
) {
  LiquidCrystal_I2C *p_I2CLCD = (LiquidCrystal_I2C*)m_Lowlevel;
  p_I2CLCD->command(byte);
}
