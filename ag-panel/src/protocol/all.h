/** @file all.h
    @brief AG-Panel Project all Keyboard includes
    @copyright (C) 2019-2026 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#pragma once

#include "AbstractProtocol.h"

#include "LoSPanelProtocol.h"
#include "RawSerialProtocol.h"

extern AbstractProtocol *initProtocol(AbstractUART *p_UART, AbstractLCD *p_LCD, AbstractKeyboard *p_Keyboard);
