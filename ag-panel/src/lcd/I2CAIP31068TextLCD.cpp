/*!
  \file I2CAIP31068TextLCD.cpp
  \brief AG-Panel Project I2C 8-bit text (AIP31068) LCD implmentation
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#include "../private.h"
#include "I2CAIP31068TextLCD.h"

#if !defined(ARDUINO_ARCH_GD32V) && !defined(ARDUINO_ARCH_KENDRYTE)

//#include <SoftSPIB.h>
#include <LiquidCrystal_AIP31068_I2C.h>

/*!
  \brief Initialization of I2C text LCD display

  Configures I2C text LCD display to work with specified geometry.
  \returns true
 */
bool I2CAIP31068TextLCD::Init() {
  m_Lowlevel = new LiquidCrystal_AIP31068_I2C(m_I2CAddress, m_Columns, m_Rows);
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = reinterpret_cast<LiquidCrystal_AIP31068_I2C*>(m_Lowlevel);
  p_I2CLCD->init();
  return true;
}

/*!
  \brief Deinitialisation of I2C text LCD display class
 */
void I2CAIP31068TextLCD::Exit() {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = reinterpret_cast<LiquidCrystal_AIP31068_I2C*>(m_Lowlevel);
  if(p_I2CLCD != nullptr)
    delete p_I2CLCD;
  m_Lowlevel = nullptr;
}

/*!
  \brief Clear LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_I2C class instance.
 */
void I2CAIP31068TextLCD::Clear() {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = reinterpret_cast<LiquidCrystal_AIP31068_I2C*>(m_Lowlevel);
  p_I2CLCD->clear();
}

/*!
  \brief Set Cursor on LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_I2C class instance.
 */
void I2CAIP31068TextLCD::SetCursor(
  uint8_t column,       /*!< Column to put the cursor to */
  uint8_t row           /*!< Row to put the cursor to */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = reinterpret_cast<LiquidCrystal_AIP31068_I2C*>(m_Lowlevel);
  p_I2CLCD->setCursor(column, row);
}

/*!
  \brief Print a text on LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_I2C class instance.
 */
void I2CAIP31068TextLCD::Print(
  const char *str       /*!< String to print */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = reinterpret_cast<LiquidCrystal_AIP31068_I2C*>(m_Lowlevel);
  p_I2CLCD->print(str);
}

/*!
  \brief Print a character on LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_I2C class instance.
 */
void I2CAIP31068TextLCD::Print(
  char character        /*!< Character to print */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = reinterpret_cast<LiquidCrystal_AIP31068_I2C*>(m_Lowlevel);
  p_I2CLCD->print(character);
}

/*!
  \brief Write a byte (RS = 1) to LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_I2C class instance.
 */
void I2CAIP31068TextLCD::Write(
  uint8_t byte          /* !< Byte to write to LCD display */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = reinterpret_cast<LiquidCrystal_AIP31068_I2C*>(m_Lowlevel);
  p_I2CLCD->write(byte);
}

/*!
  \brief Send a command byte (RS = 0) to LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_I2C class instance.
 */
void I2CAIP31068TextLCD::Command(
  uint8_t byte          /* !< Command to send to LCD display */
) {
  LiquidCrystal_AIP31068_I2C *p_I2CLCD = reinterpret_cast<LiquidCrystal_AIP31068_I2C*>(m_Lowlevel);
  p_I2CLCD->command(byte);
}

#else
#warning 'I2CAIP31068TextLCD' is not implemented for GD32V and KENDRYTE platforms bacause it lacks of standard header 'Wire.h'!
#endif /* !ARDUINO_ARCH_GD32V */
