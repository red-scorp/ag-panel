/*!
  \file PPITextLCD.h
  \brief AG-Panel Project PPI (parallel) 4 and 8-bit text (hd44780) LCD interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractTextLCD.h"

class PPITextLCD: public AbstractTextLCD {

public:
  PPITextLCD(AbstractBacklight *Backlight, uint8_t Columns, uint8_t Rows, uint8_t RSPin, uint8_t RWPin, uint8_t EnablePin, uint8_t D0Pin, uint8_t D1Pin, uint8_t D2Pin, uint8_t D3Pin, uint8_t D4Pin, uint8_t D5Pin, uint8_t D6Pin, uint8_t D7Pin): AbstractTextLCD(Backlight), m_Columns(Columns), m_Rows(Rows), m_RSPin(RSPin), m_RWPin(RWPin), m_EnablePin(EnablePin), m_D0Pin(D0Pin), m_D1Pin(D1Pin), m_D2Pin(D2Pin), m_D3Pin(D3Pin), m_D4Pin(D4Pin), m_D5Pin(D5Pin), m_D6Pin(D6Pin), m_D7Pin(D7Pin) { Init(); }
  PPITextLCD(AbstractBacklight *Backlight, uint8_t Columns, uint8_t Rows, uint8_t RSPin, uint8_t RWPin, uint8_t EnablePin, uint8_t D4Pin, uint8_t D5Pin, uint8_t D6Pin, uint8_t D7Pin): AbstractTextLCD(Backlight), m_Columns(Columns), m_Rows(Rows), m_RSPin(RSPin), m_RWPin(RWPin), m_EnablePin(EnablePin), m_D0Pin(InvalidPin), m_D1Pin(InvalidPin), m_D2Pin(InvalidPin), m_D3Pin(InvalidPin), m_D4Pin(D4Pin), m_D5Pin(D5Pin), m_D6Pin(D6Pin), m_D7Pin(D7Pin) { Init(); }
  virtual ~PPITextLCD() override { Exit(); }

  using AbstractTextLCD::SetBacklight;
  virtual void Clear() override;
  virtual void SetCursor(uint8_t row, uint8_t col) override;
  virtual void Print(const char *str) override;

  virtual void Write(uint8_t byte) override;
  virtual void Command(uint8_t byte) override;

protected:
  uint8_t m_Columns;
  uint8_t m_Rows;
  uint8_t m_RSPin;
  uint8_t m_RWPin;
  uint8_t m_EnablePin;
  uint8_t m_D0Pin;
  uint8_t m_D1Pin;
  uint8_t m_D2Pin;
  uint8_t m_D3Pin;
  uint8_t m_D4Pin;
  uint8_t m_D5Pin;
  uint8_t m_D6Pin;
  uint8_t m_D7Pin;

private:
  bool Init();
  void Exit();
};
