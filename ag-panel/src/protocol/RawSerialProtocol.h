/*! \file RawSerialProtocol.h
    \brief AG-Panel Project raw serial protocol interface
    \copyright (C) 2020-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractProtocol.h"

/*! \brief Raw Serial class

    This class implements a raw serial (debug) protocol.
 */
class RawSerialProtocol: public AbstractProtocol {

public:
    explicit RawSerialProtocol(
        AbstractUART *UART,           /*!< Pointer to UART implementation */
        AbstractLCD *LCD,             /*!< Pointer to LCD implementation */
        AbstractKeyboard *Keyboard    /*!< Pointer to keyboard implementation */
    ): AbstractProtocol(UART, LCD, Keyboard),
        m_XPos(0),
        m_YPos(0),
        m_OutOfRange(false),
        m_ShowRealData(false) { Init(); }
    virtual ~RawSerialProtocol() { Exit(); }

    virtual void Loop() override;
    virtual void Yield() override;

protected:

private:
    uint32_t m_XPos;      /*!< Current X postion on display */
    uint32_t m_YPos;      /*!< Current Y postion on display */
    bool m_OutOfRange;    /*!< Out Of character buffer Range condition */
    bool m_ShowRealData;  /*!< We already have real data on LCD condition (in opposite to splash screen mode) */
    bool Init();
    void Exit();
};
