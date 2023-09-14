/** @file LoSPanelProtocol.h
    @brief AG-Panel Project LoS-panel protocol interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractProtocol.h"
#include "../lcd/AbstractTextLCD.h"

/** @brief LoS Panel class

    This class implements a LoS (LCD over Serial) panel protocol.
 */
class LoSPanelProtocol: public AbstractProtocol {

public:
    explicit LoSPanelProtocol(
        AbstractUART *UART,           /**< Pointer to UART implementation */
        AbstractTextLCD *TextLCD,     /**< Pointer to text LCD implementation */
        AbstractKeyboard *Keyboard    /**< Pointer to keyboard implementation */
    ): AbstractProtocol(UART, TextLCD, Keyboard),
        m_TextLCD(TextLCD) { Init(); }
    virtual ~LoSPanelProtocol() { Exit(); }

    virtual void Loop() override;
    virtual void Yield() override;

protected:
    AbstractTextLCD *m_TextLCD;     /**< Pointer to text LCD implementation */

private:
    uint32_t m_LCDLastTxMicros;     /**< Last LCD transfer microseconds time stamp value */
    uint8_t m_LCDLastTxCommand;     /**< Last LCD transfer command value to determine the waiting time */
    bool Init();
    void Exit();
    void WaitFromLastTx(uint32_t WaitMicros);
    void StampLastTx();
};
