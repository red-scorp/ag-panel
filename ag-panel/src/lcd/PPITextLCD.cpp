/*!
  \file PPITextLCD.cpp
  \brief AG-Panel Project PPI (parallel) 4 and 8-bit text (hd44780) LCD implmentation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "PPITextLCD.h"
#include <LiquidCrystal.h>

static LiquidCrystal *sp_PPILCD;

bool PPITextLCD::Init() {
  if(m_D0Pin != InvalidPin && m_D1Pin != InvalidPin && m_D2Pin != InvalidPin && m_D3Pin != InvalidPin)
    sp_PPILCD = new LiquidCrystal(m_RSPin, m_RWPin, m_EnablePin, m_D0Pin, m_D1Pin, m_D2Pin, m_D3Pin, m_D4Pin, m_D5Pin, m_D6Pin, m_D7Pin);
  else
    sp_PPILCD = new LiquidCrystal(m_RSPin, m_RWPin, m_EnablePin, m_D4Pin, m_D5Pin, m_D6Pin, m_D7Pin);
  sp_PPILCD->begin(m_Columns, m_Rows);
  return true;
}

void PPITextLCD::Exit() {
}

void PPITextLCD::Clear() {
  sp_PPILCD->clear();
}

void PPITextLCD::SetCursor(uint8_t column, uint8_t row) {
  sp_PPILCD->setCursor(column, row);
}

void PPITextLCD::Print(const char *str) {
  sp_PPILCD->print(str);
}

void PPITextLCD::Write(uint8_t byte) {
  sp_PPILCD->write(byte);
}

void PPITextLCD::Command(uint8_t byte) {
  sp_PPILCD->command(byte);
}
