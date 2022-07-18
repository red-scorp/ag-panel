/*! \file NoneUART.h
    \brief AG-Panel Project none UART interface
    \copyright (C) 2019-2022 Andriy Golovnya
    \author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractUART.h"

/*! \brief None UART class

    This is a class which implements none UART.
 */
class NoneUART: public AbstractUART {

public:
    explicit NoneUART(
        uint32_t BaudRate = DefaultUARTBaudRate   /*!< Baud rate of an UART */
    ): AbstractUART(BaudRate) { Init(); }
    virtual ~NoneUART() override { Exit(); }

    virtual uint8_t PutCh(uint8_t txbyte) override;
    virtual uint8_t GetCh() override;
    virtual uint32_t Available() override;

protected:

private:
    bool Init();
    void Exit();
};
