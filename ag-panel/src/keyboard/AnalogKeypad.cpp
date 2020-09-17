/*!
  \file AnalogKeypad.cpp
  \brief AG-Panel Project analog keypad keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "../../config.h"
#include "AnalogKeypad.h"

/*!
  \brief Initialization of analog keypad

  \returns true
 */
bool AnalogKeypad::Init() {
  /* No initialization needed for analog pins */
  return true;
}

/*!
  \brief Deinitialisation of analog keypad class
 */
void AnalogKeypad::Exit() {
}

/*!
  \brief Get a key of analog keypad

  Reads analog pin and deduces what key has been pressed.
  \returns #KeyNone if no new actions detected, else a key code
 */
uint8_t AnalogKeypad::GetKey() {
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

/*!
  \brief Get number of keys supported by analog leybad

  \returns Number of supported keys
 */
uint8_t AnalogKeypad::GetKeyCount() {
  return 5;
}
