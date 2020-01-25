/*!
  \file I2CAIP31068TextLCD.cpp
  \brief AG-Panel Project I2C 8-bit text (AIP31068) LCD implmentation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "I2CAIP31068TextLCD.h"
#include <SoftSPIB.h>
#include <LiquidCrystal_AIP31068_I2C.h>

/*!
  \brief Initialization of I2C text LCD display

  Configures I2C text LCD display to work with specified geometry.
  \returns true
 */
bool I2CAIP31068TextLCD::Init() {
  m_Lowlevel = new LiquidCrystal_AIP31068_I2C(m_I2CAddress, m_Columns, m_Rows);
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = (LiquidCrystal_AIP31068_I2C*)m_Lowlevel;
  p_I2CLCD->init();
  return true;
}

/*!
  \brief Deinitialisation of I2C text LCD display class
 */
void I2CAIP31068TextLCD::Exit() {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = (LiquidCrystal_AIP31068_I2C*)m_Lowlevel;
  if(p_I2CLCD != nullptr)
    delete p_I2CLCD;
  m_Lowlevel = nullptr;
}

/*!
  \brief Set backlight in binary (on/off) form

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CAIP31068TextLCD::SetBacklight(
  bool on               /*!< Backlight state in on/off format */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = (LiquidCrystal_AIP31068_I2C*)m_Lowlevel;
  if(on)
    p_I2CLCD->backlight();
  else
    p_I2CLCD->noBacklight();
}

/*!
  \brief Set backlight brightness if supported

  This function enables LCD backlight if brightness is non-zero.
 */
void I2CAIP31068TextLCD::SetBacklight(
  uint8_t brightness    /*!< Backlight brightness value */
) {
  SetBacklight(bool(brightness > 0? true: false));
}

/*!
  \brief Set backlight RGB colors if supported

  This function enables LCD backlight if RGB is non-zero.
 */
void I2CAIP31068TextLCD::SetBacklight(
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
void I2CAIP31068TextLCD::SetBacklight(
  uint32_t rgb          /*!< RGB integer value */
) {
  SetBacklight(bool(rgb > 0? true: false));
}

/*!
  \brief Clear LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CAIP31068TextLCD::Clear() {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = (LiquidCrystal_AIP31068_I2C*)m_Lowlevel;
  p_I2CLCD->clear();
}

/*!
  \brief Set Cursor on LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CAIP31068TextLCD::SetCursor(
  uint8_t column,       /*!< Column to put the cursor to */
  uint8_t row           /*!< Row to put the cursor to */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = (LiquidCrystal_AIP31068_I2C*)m_Lowlevel;
  p_I2CLCD->setCursor(column, row);
}

/*!
  \brief Print a text on LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CAIP31068TextLCD::Print(
  const char *str       /*!< String to print */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = (LiquidCrystal_AIP31068_I2C*)m_Lowlevel;
  p_I2CLCD->print(str);
}

/*!
  \brief Write a byte (RS = 1) to LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CAIP31068TextLCD::Write(
  uint8_t byte          /* !< Byte to write to LCD display */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = (LiquidCrystal_AIP31068_I2C*)m_Lowlevel;
  p_I2CLCD->write(byte);
}

/*!
  \brief Send a command byte (RS = 0) to LCD display

  This function calls corresponding function of LiquidCrystal_I2C class instance.
 */
void I2CAIP31068TextLCD::Command(
  uint8_t byte          /* !< Command to send to LCD display */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = (LiquidCrystal_AIP31068_I2C*)m_Lowlevel;
  p_I2CLCD->command(byte);
}
