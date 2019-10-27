/*!
  \file DigitalMatrix.cpp
  \brief AG-Panel Project digital keypad keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"
#include "DigitalMatrix.h"

bool DigitalMatrix::Init() {

  for(uint8_t c = 0 ; c < m_Columns; c++)
    pinMode(m_CPinsArray[c], OUTPUT);
  for(uint8_t r = 0 ; r < m_Rows; r++)
    pinMode(m_RPinsArray[r], OUTPUT);

  return true;
}

void DigitalMatrix::Exit() {
}

uint8_t DigitalMatrix::GetKey() {

  for(uint8_t c = 0; c < m_Columns; c++) {
    delayMicroseconds(5);
    for(uint8_t i = 0; i < m_Columns; i++) {
      digitalWrite(m_CPinsArray[i], i == c? LOW: HIGH);
    }
    delayMicroseconds(5);
    for(uint8_t r = 0; r < m_Rows; r++) {
      uint16_t v = analogRead(m_RPinsArray[r]);
      if(v < 100) {
        for(uint8_t i = 0; i < m_Columns; i++) {
          digitalWrite(m_CPinsArray[i], HIGH);
        }
        return r * m_Columns + c + 1;
      }
    }
  }
  for(uint8_t i = 0; i < m_Columns; i++) {
    digitalWrite(m_CPinsArray[i], HIGH);
  }
  return KeyNone;
}
