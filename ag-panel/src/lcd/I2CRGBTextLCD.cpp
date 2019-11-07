/*!
  \file I2CRGBTextLCD.cpp
  \brief AG-Panel Project I2C RGB keypad's text (hd44780) LCD implmentation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "I2CRGBTextLCD.h"
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield *gp_I2CRGBLCD;

bool I2CRGBTextLCD::Init() {
  gp_I2CRGBLCD = new Adafruit_RGBLCDShield;
  gp_I2CRGBLCD->begin(m_Columns, m_Rows);
  /* TODO: add usage of m_I2CAddress */
  return true;
}

void I2CRGBTextLCD::Exit() {
}

void I2CRGBTextLCD::SetBacklight(bool on) {
  SetBacklight(uint32_t(on? m_DefaultColor: 0));
}

void I2CRGBTextLCD::SetBacklight(uint8_t brightness) {
  SetBacklight(uint32_t(brightness > 0? m_DefaultColor: 0));
}

void I2CRGBTextLCD::SetBacklight(uint8_t red, uint8_t green, uint8_t blue) {
  gp_I2CRGBLCD->setBacklight((red > 0? 0x01: 0x00) | (green > 0? 0x02: 0x00) | (blue > 0? 0x04: 0x00));
}

void I2CRGBTextLCD::SetBacklight(uint32_t rgb) {
  SetBacklight(RGBUint2Red(rgb), RGBUint2Green(rgb), RGBUint2Blue(rgb));
}

void I2CRGBTextLCD::Clear() {
  gp_I2CRGBLCD->clear();
}

void I2CRGBTextLCD::SetCursor(uint8_t column, uint8_t row) {
  gp_I2CRGBLCD->setCursor(column, row);
}

void I2CRGBTextLCD::Print(const char *str) {
  gp_I2CRGBLCD->print(str);
}

void I2CRGBTextLCD::Write(uint8_t byte) {
  gp_I2CRGBLCD->write(byte);
}

void I2CRGBTextLCD::Command(uint8_t byte) {
  gp_I2CRGBLCD->command(byte);
}
