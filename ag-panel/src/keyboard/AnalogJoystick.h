/** @file AnalogJoystick.h
    @brief AG-Panel Project analog joystick keyboard interface
    @copyright (C) 2019-2023 Andriy Golovnya
    @author Andriy Golovnya (andriy.golovnya@gmail.com)
 */

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

/** @brief Analog Joystick class

    This class implements analog joystick based on two 10k potentiometers and a button.
 */
class AnalogJoystick: public AbstractKeyboard {

public:
    explicit AnalogJoystick(
        uint8_t XPin,       /**< X-direction potentiometer analog pin */
        uint8_t YPin,       /**< Y-direction potentiometer analog pin */
        uint8_t ButtonPin   /**< Select button digital pin */
    ): AbstractKeyboard(),
        m_XPin(XPin),
        m_YPin(YPin),
        m_ButtonPin(ButtonPin) { Init(); }
    virtual ~AnalogJoystick() override { Exit(); }

    virtual uint8_t GetKey() override;
    virtual uint8_t GetKeyCount() override;

protected:
    uint8_t m_XPin;       /**< X-direction potentiometer analog pin */
    uint8_t m_YPin;       /**< Y-direction potentiometer analog pin */
    uint8_t m_ButtonPin;  /**< Select button digital pin */

private:
    bool Init();
    void Exit();
};
