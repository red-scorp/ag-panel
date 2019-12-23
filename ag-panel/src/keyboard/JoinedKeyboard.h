/*!
  \file JoinedKeyboard.h
  \brief AG-Panel Project joined keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/*!
  \brief Joined Keyboard class

  This class implements joined keyboard (complex keyboard).
 */
class JoinedKeyboard: public AbstractKeyboard {

public:
  JoinedKeyboard():
    AbstractKeyboard(),
    m_Privat(nullptr) { Init(); }
  virtual ~JoinedKeyboard() override { Exit(); }

  virtual uint8_t GetKey() override;
  virtual uint8_t GetKeyCount() override;

  void AddKeyboard(AbstractKeyboard *keyboard);

protected:

private:
  void *m_Privat;       /*!< Pointer to Low-Level privat class */
  bool Init();
  void Exit();
};
