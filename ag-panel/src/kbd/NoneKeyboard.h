/*!
  \file NoneKeyboard.h
  \brief AG-Panel Project none keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

class NoneKeyboard: public AbstractKeyboard {

public:
  NoneKeyboard(): AbstractKeyboard() { Init(); }
  virtual ~NoneKeyboard() { Exit(); }

  virtual uint8_t GetKey() override;

protected:

private:
  bool Init();
  void Exit();
};
