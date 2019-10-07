/*!
  \file NoneKeyboard.cpp
  \brief AG-Panel Project none keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#include "../private.h"
#include "NoneKeyboard.h"

bool NoneKeyboard::Init() {
  return true;
}

void NoneKeyboard::Exit() {
}

uint8_t NoneKeyboard::GetKey() {
  return KeyNone;
}
