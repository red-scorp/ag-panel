/*!
  \file AnalogKeypadKeyboard.cpp
  \brief AG-Panel Project analog keypad keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"
#include "AnalogKeypadKeyboard.h"

bool AnalogKeypadKeyboard::Init() {
  /* no initialization needed for analog pins */
  return true;
}

void AnalogKeypadKeyboard::Exit() {
}

uint8_t AnalogKeypadKeyboard::GetKey() {
  uint16_t data = analogRead(m_AnalogKeypadPin);
  if(data >= KBD_DATA_UP_MIN && data < KBD_DATA_UP_MAX)
    return KeyDefaultUp;
  if(data >= KBD_DATA_DOWN_MIN && data < KBD_DATA_DOWN_MAX)
    return KeyDefaultDown;
  if(data >= KBD_DATA_LEFT_MIN && data < KBD_DATA_LEFT_MAX)
    return KeyDefaultLeft;
  if(data >= KBD_DATA_RIGHT_MIN && data < KBD_DATA_RIGHT_MAX)
    return KeyDefaultRight;
  if(data >= KBD_DATA_SELECT_MIN && data < KBD_DATA_SELECT_MAX)
    return KeyDefaultSelect;
  return KeyNone;
}
