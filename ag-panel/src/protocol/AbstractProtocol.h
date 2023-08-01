/** @file AbstractProtocol.h
    @brief AG-Panel Project abstract protocol interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "../uart/AbstractUART.h"
#include "../lcd/AbstractLCD.h"
#include "../keyboard/AbstractKeyboard.h"

/** @brief Abstract Protocol class

    This is a base class for all protocol implementations.
    It defines only a base interface of protocol used by the rest of a project code.
 */
class AbstractProtocol {

public:
    explicit AbstractProtocol(
        AbstractUART *UART,         /**< Pointer to UART implementation */
        AbstractLCD *LCD,           /**< Pointer to LCD implementation */
        AbstractKeyboard *Keyboard  /**< Pointer to keyboard implementation */
    ): m_UART(UART),
        m_LCD(LCD),
        m_Keyboard(Keyboard) { Init(); }
    virtual ~AbstractProtocol() { Exit(); }

    virtual void Loop() = 0;
    virtual void Yield() = 0;

protected:
    AbstractUART *m_UART;         /**< Pointer to UART implementation */
    AbstractLCD *m_LCD;           /**< Pointer to LCD implementation */
    AbstractKeyboard *m_Keyboard; /**< Pointer to keyboard implementation */

private:
    bool Init() { return true; }
    void Exit() {}
};
