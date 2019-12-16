/*!
  \file SimpleButton.cpp
  \brief AG-Panel Project simple button keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "../../config.h"
#include "SimpleButton.h"

/*!
  \brief Initialization of simple button(s)

  Configures button(s) pins.
  \returns true
 */
bool SimpleButton::Init() {

  for(uint8_t i = 0; i < m_Number; i++)
    pinMode(m_PinsArray[i], OUTPUT);

  return true;
}

/*!
  \brief Deinitialisation of simple button class
 */
void SimpleButton::Exit() {
}

/*!
  \brief Get a key of simple button array

  Sequntially reads button pins to find out what key has been pressed.
  \returns #KeyNone if no new actions detected, else a key code
 */
uint8_t SimpleButton::GetKey() {
  for(uint8_t i = 0; i < m_Number; i++) {
    uint16_t v = analogRead(m_PinsArray[i]);
    if(v < 100) {
      return i + 1;
    }
  }
  return KeyNone;
}
