/*!
  \file NoneKeyboard.h
  \brief AG-Panel Project none keyboard interface
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/*!
  \brief None Keyboard class

  This class implements none keyboard (missing keyboard).
 */
class NoneKeyboard: public AbstractKeyboard {

public:
  explicit NoneKeyboard(): AbstractKeyboard() { Init(); }
  virtual ~NoneKeyboard() override { Exit(); }

  virtual uint8_t GetKey() override;
  virtual uint8_t GetKeyCount() override;

protected:

private:
  bool Init();
  void Exit();
};
