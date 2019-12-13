/*!
  \file NoneKeyboard.cpp
  \brief AG-Panel Project none keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "NoneKeyboard.h"

/*!
  \brief Initialization of none keyboard

  \returns true
 */
bool NoneKeyboard::Init() {
  return true;
}

/*!
  \brief Deinitialisation of none keyboard class
 */
void NoneKeyboard::Exit() {
}

/*!
  \brief Get a key of none keyboard

  \returns #KeyNone allways
 */
uint8_t NoneKeyboard::GetKey() {
  return KeyNone;
}
