/*!
  \file init.cpp
  \brief AG-Panel Project Keyboard initialization
  \copyright (C) 2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#include "../private.h"
#include "../../config.h"

#include "all.h"

/*!
  \brief Initialize protocol

  This function chooses one of protocol classes to use based on configuration defined in config.h
  \returns Pointer to protocol class
 */
AbstractProtocol *initProtocol(AbstractUART *UART, AbstractLCD *LCD, AbstractKeyboard *Keyboard) {
  AbstractProtocol *p_Protocol = nullptr;

  #if defined(PROT_LOSPANEL)
    p_Protocol = new LoSPanelProtocol(UART, reinterpret_cast<AbstractTextLCD*>(LCD), Keyboard);
  #elif defined(PROT_RAWSERIAL)
    p_Protocol = new RawSerialProtocol(UART, LCD, Keyboard);
  #else
    #error Protocol is not defined!
  #endif

  return p_Protocol;
}
