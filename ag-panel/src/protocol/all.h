/*!
  \file all.h
  \brief AG-Panel Project all Keyboard includes
  \copyright (C) 2019-2020 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#pragma once

#include "AbstractProtocol.h"

#include "LoSPanelProtocol.h"
#include "RawSerialProtocol.h"

extern AbstractProtocol *initProtocol(AbstractUART *UART, AbstractLCD *LCD, AbstractKeyboard *Keyboard);
