/*!
  \file SPIAIP31068TextLCD.cpp
  \brief AG-Panel Project SPI 8-bit text (AIP31068) LCD implmentation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "SPIAIP31068TextLCD.h"
#include <SoftSPIB.h>
#include <LiquidCrystal_AIP31068_SPI.h>

/*!
  \brief Initialization of SPI text LCD display

  Configures SPI text LCD display to work with specified geometry.
  \returns true
 */
bool SPIAIP31068TextLCD::Init() {
  m_Lowlevel = new LiquidCrystal_AIP31068_SPI(m_SSPin, m_Columns, m_Rows, m_SCLKPin, m_MOSIPin, m_MISOPin);
  LiquidCrystal_AIP31068_SPI *p_SPILCD = (LiquidCrystal_AIP31068_SPI*)m_Lowlevel;
  p_SPILCD->init();
  return true;
}

/*!
  \brief Deinitialisation of I2C text LCD display class
 */
void SPIAIP31068TextLCD::Exit() {
  LiquidCrystal_AIP31068_SPI *p_SPILCD = (LiquidCrystal_AIP31068_SPI*)m_Lowlevel;
  if(p_SPILCD != nullptr)
    delete p_SPILCD;
  m_Lowlevel = nullptr;
}

/*!
  \brief Clear LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_SPI class instance.
 */
void SPIAIP31068TextLCD::Clear() {
  LiquidCrystal_AIP31068_SPI *p_SPILCD = (LiquidCrystal_AIP31068_SPI*)m_Lowlevel;
  p_SPILCD->clear();
}

/*!
  \brief Set Cursor on LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_SPI class instance.
 */
void SPIAIP31068TextLCD::SetCursor(
  uint8_t column,       /*!< Column to put the cursor to */
  uint8_t row           /*!< Row to put the cursor to */
) {
  LiquidCrystal_AIP31068_SPI *p_SPILCD = (LiquidCrystal_AIP31068_SPI*)m_Lowlevel;
  p_SPILCD->setCursor(column, row);
}

/*!
  \brief Print a text on LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_SPI class instance.
 */
void SPIAIP31068TextLCD::Print(
  const char *str       /*!< String to print */
) {
  LiquidCrystal_AIP31068_SPI *p_SPILCD = (LiquidCrystal_AIP31068_SPI*)m_Lowlevel;
  p_SPILCD->print(str);
}

/*!
  \brief Write a byte (RS = 1) to LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_SPI class instance.
 */
void SPIAIP31068TextLCD::Write(
  uint8_t byte          /* !< Byte to write to LCD display */
) {
  LiquidCrystal_AIP31068_SPI *p_SPILCD = (LiquidCrystal_AIP31068_SPI*)m_Lowlevel;
  p_SPILCD->write(byte);
}

/*!
  \brief Send a command byte (RS = 0) to LCD display

  This function calls corresponding function of LiquidCrystal_AIP31068_SPI class instance.
 */
void SPIAIP31068TextLCD::Command(
  uint8_t byte          /* !< Command to send to LCD display */
) {
  LiquidCrystal_AIP31068_SPI *p_SPILCD = (LiquidCrystal_AIP31068_SPI*)m_Lowlevel;
  p_SPILCD->command(byte);
}
