/** @file RotaryEncoder.h
    @brief AG-Panel Project rotary encoder keyboard interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/** @brief Digital Matrix class

    This class implements rotary encoder based on two digital pins for encoder an single digital pin for select key.
 */
class RotaryEncoder: public AbstractKeyboard {

public:
    explicit RotaryEncoder(
        uint8_t D1Pin,        /**< First digital pin of rotary encoder */
        uint8_t D2Pin,        /**< Second digital pin of rotary encoder */
        uint8_t ButtonPin     /**< Digital pin of select button */
    ): AbstractKeyboard(),
        m_D1Pin(D1Pin),
        m_D2Pin(D2Pin),
        m_ButtonPin(ButtonPin) { Init(); }
    virtual ~RotaryEncoder() override { Exit(); }

    virtual uint8_t GetKey() override;
    virtual uint8_t GetKeyCount() override;

protected:
    uint8_t m_D1Pin;        /**< First digital pin of rotary encoder */
    uint8_t m_D2Pin;        /**< Second digital pin of rotary encoder */
    uint8_t m_ButtonPin;    /**< Digital pin of select button */

private:
    bool Init();
    void Exit();
};
