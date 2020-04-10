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
  explicit JoinedKeyboard():
    AbstractKeyboard(),
    m_Privat(nullptr) { Init(); }
  explicit JoinedKeyboard(
    AbstractKeyboard *Keyboard          /*!< Keyboard class instance we want to inlist first */
  ): AbstractKeyboard(),
    m_Privat(nullptr) {
    Init();
    AddKeyboard(Keyboard);
  }
  explicit JoinedKeyboard(
    AbstractKeyboard *Keyboard1,        /*!< Keyboard class instance we want to inlist first */
    AbstractKeyboard *Keyboard2         /*!< Keyboard class instance we want to inlist second */
  ): AbstractKeyboard(),
    m_Privat(nullptr) {
    Init();
    AddKeyboard(Keyboard1);
    AddKeyboard(Keyboard2);
  }
  explicit JoinedKeyboard(
    AbstractKeyboard *Keyboard1,        /*!< Keyboard class instance we want to inlist first */
    AbstractKeyboard *Keyboard2,        /*!< Keyboard class instance we want to inlist second */
    AbstractKeyboard *Keyboard3         /*!< Keyboard class instance we want to inlist 3rd */
  ): AbstractKeyboard(),
    m_Privat(nullptr) {
    Init();
    AddKeyboard(Keyboard1);
    AddKeyboard(Keyboard2);
    AddKeyboard(Keyboard3);
  }
  explicit JoinedKeyboard(
    AbstractKeyboard *Keyboard1,        /*!< Keyboard class instance we want to inlist first */
    AbstractKeyboard *Keyboard2,        /*!< Keyboard class instance we want to inlist second */
    AbstractKeyboard *Keyboard3,        /*!< Keyboard class instance we want to inlist 3rd */
    AbstractKeyboard *Keyboard4         /*!< Keyboard class instance we want to inlist 4th */
  ): AbstractKeyboard(),
    m_Privat(nullptr) {
    Init();
    AddKeyboard(Keyboard1);
    AddKeyboard(Keyboard2);
    AddKeyboard(Keyboard3);
    AddKeyboard(Keyboard4);
  }
  explicit JoinedKeyboard(
    AbstractKeyboard *Keyboard1,        /*!< Keyboard class instance we want to inlist first */
    AbstractKeyboard *Keyboard2,        /*!< Keyboard class instance we want to inlist second */
    AbstractKeyboard *Keyboard3,        /*!< Keyboard class instance we want to inlist 3rd */
    AbstractKeyboard *Keyboard4,        /*!< Keyboard class instance we want to inlist 4th */
    AbstractKeyboard *Keyboard5         /*!< Keyboard class instance we want to inlist 5th */
  ): AbstractKeyboard(),
    m_Privat(nullptr) {
    Init();
    AddKeyboard(Keyboard1);
    AddKeyboard(Keyboard2);
    AddKeyboard(Keyboard3);
    AddKeyboard(Keyboard4);
    AddKeyboard(Keyboard5);
  }
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
