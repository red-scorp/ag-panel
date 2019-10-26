/*!
  \file AnalogKeypadKeyboard.cpp
  \brief AG-Panel Project analog keypad keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "../../config.h"
#include "AnalogKeypadKeyboard.h"

/* TODO: Change all KBD_DATA_* macros to constants */
#define KBD_DATA_NONE_MIN   700
#define KBD_DATA_NONE_MAX   1023
#define KBD_DATA_UP_MIN     50
#define KBD_DATA_UP_MAX     150
#define KBD_DATA_DOWN_MIN   150
#define KBD_DATA_DOWN_MAX   350
#define KBD_DATA_LEFT_MIN   350
#define KBD_DATA_LEFT_MAX   550
#define KBD_DATA_RIGHT_MIN  0
#define KBD_DATA_RIGHT_MAX  50
#define KBD_DATA_SELECT_MIN 550
#define KBD_DATA_SELECT_MAX 700

bool AnalogKeypadKeyboard::Init() {
  /* no initialization needed for analog pins */
  return true;
}

void AnalogKeypadKeyboard::Exit() {
}

uint8_t AnalogKeypadKeyboard::GetKey() {

  uint16_t data = analogRead(m_DataPin);

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
