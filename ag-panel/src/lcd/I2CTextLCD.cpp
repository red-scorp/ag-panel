/*!
  \file I2CTextLCD.cpp
  \brief AG-Panel Project I2C 4-bit text (hd44780) LCD implmentation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "I2CTextLCD.h"
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C *sp_I2CLCD;

bool I2CTextLCD::Init() {
  sp_I2CLCD = new LiquidCrystal_I2C(m_I2CAddress, m_Columns, m_Rows);
  sp_I2CLCD->init();
  return true;
}

void I2CTextLCD::Exit() {
}

void I2CTextLCD::SetBacklight(bool on) {
  if(on)
    sp_I2CLCD->backlight();
  else
    sp_I2CLCD->noBacklight();
}

void I2CTextLCD::SetBacklight(uint8_t brightness) {
  SetBacklight(bool(brightness > 0? true: false));
}

void I2CTextLCD::SetBacklight(uint8_t red, uint8_t green, uint8_t blue) {
  SetBacklight(bool(red > 0 || green > 0 || blue > 0? true: false));
}

void I2CTextLCD::SetBacklight(uint32_t rgb) {
  SetBacklight(bool(rgb > 0? true: false));
}

void I2CTextLCD::Clear() {
  sp_I2CLCD->clear();
}

void I2CTextLCD::SetCursor(uint8_t column, uint8_t row) {
  sp_I2CLCD->setCursor(column, row);
}

void I2CTextLCD::Print(const char *str) {
  sp_I2CLCD->print(str);
}

void I2CTextLCD::Write(uint8_t byte) {
  sp_I2CLCD->write(byte);
}

void I2CTextLCD::Command(uint8_t byte) {
  sp_I2CLCD->command(byte);
}
