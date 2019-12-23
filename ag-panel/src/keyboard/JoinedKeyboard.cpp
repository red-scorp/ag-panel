/*!
  \file JoinedKeyboard.cpp
  \brief AG-Panel Project joined keyboard implementation
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
 */

#include "../private.h"
#include "JoinedKeyboard.h"

/*!
  \brief Joined Keyboard List class

  This class implements joined keyboard linked list entry containing a pointer to a keyboard class and its metadata.
 */
class JoinedKeyboardList {

public:
  JoinedKeyboardList(
    AbstractKeyboard *Keyboard,     /*!< Pointer to a keyboard to add in the list */
    uint8_t KeyOffset               /*!< Offset of the first key this keyboard generates */
  ): m_Keyboard(Keyboard),
    m_KeyOffset(KeyOffset),
    m_Next(nullptr) {
    m_KeyCount = Keyboard->GetKeyCount();
  };

  ~JoinedKeyboardList() {
    if(m_Keyboard != nullptr)
      delete m_Keyboard;
    if(m_Next != nullptr)
      delete m_Next;
  };

  AbstractKeyboard *m_Keyboard;     /*!< Pointer to a Keyboard class */
  uint8_t m_KeyOffset;              /*!< Offset of the first key this keyboard class */
  uint8_t m_KeyCount;               /*!< Number of keys this keyboard class generates */
  JoinedKeyboardList *m_Next;       /*!< Pointer to a net list entry class */
};

/*!
  \brief Initialization of joined keyboard

  \returns true
 */
bool JoinedKeyboard::Init() {
  return true;
}

/*!
  \brief Deinitialisation of joined keyboard class
 */
void JoinedKeyboard::Exit() {
  if(m_Privat != nullptr) {
    JoinedKeyboardList *p_ListEntry = (JoinedKeyboardList*)m_Privat;
    delete p_ListEntry;
  }
}

/*!
  \brief Get a key of joined keyboard

  This function runs through the keyboard list and calls their \a GetKey() to find first pressed key.
  When key is found the function returns with key code added with key offset calculated in \a AddKeyboard() function.
  \returns #KeyNone if no new actions detected, else a key code
 */
uint8_t JoinedKeyboard::GetKey() {
  JoinedKeyboardList *p_ListEntry = (JoinedKeyboardList*)m_Privat;

  while(p_ListEntry != nullptr) {
    uint8_t Key = p_ListEntry->m_Keyboard->GetKey();
    if(Key != KeyNone) {
      return Key + p_ListEntry->m_KeyOffset;
    }
    p_ListEntry = p_ListEntry->m_Next;
  }

  return KeyNone;
}

/*!
  \brief Add a keyboard to the joined keyboard list

  This function add given keyboard class to the end of a linked list and assigns an offset to its key values.
 */
void JoinedKeyboard::AddKeyboard(
  AbstractKeyboard *Keyboard      /*!< Keyboard class instance we want to inlist */
) {
  JoinedKeyboardList *p_ListEntry = (JoinedKeyboardList*)m_Privat;
  JoinedKeyboardList **pp_LastNext = (JoinedKeyboardList **)&m_Privat;
  uint8_t KeyOffset = 0;

  /* Fild last linked list entry */
  while(p_ListEntry != nullptr) {
    KeyOffset = p_ListEntry->m_KeyOffset + p_ListEntry->m_KeyCount;
    pp_LastNext = &p_ListEntry->m_Next;
    p_ListEntry = p_ListEntry->m_Next;
  }

  JoinedKeyboardList *p_NewListEntry = new JoinedKeyboardList(Keyboard, KeyOffset);
  *pp_LastNext = p_NewListEntry;
}

/*!
  \brief Get number of keys supported by joined keyboard

  \returns Number of supported keys
 */
uint8_t JoinedKeyboard::GetKeyCount() {
  JoinedKeyboardList *p_ListEntry = (JoinedKeyboardList*)m_Privat;
  uint8_t KeySum = 0;

  while(p_ListEntry != nullptr) {
    KeySum += p_ListEntry->m_Keyboard->GetKeyCount();
    p_ListEntry = p_ListEntry->m_Next;
  }

  return 0;
}
