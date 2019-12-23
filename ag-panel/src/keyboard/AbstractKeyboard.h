/*!
  \file AbstractKeyboard.h
  \brief AG-Panel Project abstract keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"

/*! \brief Default key codes returned a keyboard class function \a GetKey() */
const uint8_t KeyNone = 0;            /* No key is pressed */
const uint8_t KeyDefaultUp = 1;       /* KeyMatrix_1_1=Up */
const uint8_t KeyDefaultDown = 2;     /* KeyMatrix_1_2=Down */
const uint8_t KeyDefaultLeft = 3;     /* KeyMatrix_1_3=Left */
const uint8_t KeyDefaultRight = 4;    /* KeyMatrix_1_4=Right */
const uint8_t KeyDefaultSelect = 5;   /* KeyMatrix_2_1=Enter */

/*!
  \brief Abstract keyboard class

  This is a base class for all keyboard implementations.
  It defines only a base interface of keyboard used by the rest of a project code.
 */
class AbstractKeyboard {

public:
  AbstractKeyboard() { Init(); }
  virtual ~AbstractKeyboard() { Exit(); }

  virtual uint8_t GetKey() = 0;
  virtual uint8_t GetKeyCount() = 0;

protected:

private:
  bool Init() { return true; }
  void Exit() {}
};
