/** @file init.cpp
    @brief AG-Panel Project Keyboard initialization
    @copyright (C) 2020-2026 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
*/

#include "../private.h"
#include "../../config.h"

#include "all.h"

/** @brief Initialize protocol

    This function chooses one of protocol classes to use based on configuration defined in config.h
    @returns Pointer to protocol class
 */
AbstractProtocol *initProtocol(
    AbstractUART *p_UART,           /**< Pointer to UART class */
    AbstractLCD *p_LCD,             /**< Pointer to LCD class */
    AbstractKeyboard *p_Keyboard    /**< Pointer to keyboard class */
) {
    AbstractProtocol *p_Protocol = nullptr;

    #if defined(PROT_LOSPANEL)
        p_Protocol = new LoSPanelProtocol(p_UART, reinterpret_cast<AbstractTextLCD*>(p_LCD), p_Keyboard);
    #elif defined(PROT_RAWSERIAL)
        p_Protocol = new RawSerialProtocol(p_UART, p_LCD, p_Keyboard);
    #else
        #error Protocol is not defined!
    #endif

    return p_Protocol;
}
