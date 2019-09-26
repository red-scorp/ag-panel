/*!
  \file AbstractKeyboard.h
  \brief AG-Panel Project abstract keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"

class AbstractKeyboard {

public:
  AbstractKeyboard() { Init(); }
  virtual ~AbstractKeyboard() { Exit(); }

  virtual uint8_t GetKey() = 0;

protected:

private:
  bool Init() { return true; }
  void Exit() {}
};
