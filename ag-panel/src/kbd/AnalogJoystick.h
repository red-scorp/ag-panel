/*!
  \file AnalogJoystick.h
  \brief AG-Panel Project analog joystick keyboard interface
  \copyright (C) 2019 Andriy Golovnya
  \author Andriy Golovnya (andriy.golovnya@googlemail.com)
*/

#pragma once

#include "../private.h"
#include "AbstractKeyboard.h"

const uint8_t DefaultAnalogJoystickXPin = A0;       /*!< Default X-direction analog pin */
const uint8_t DefaultAnalogJoystickYPin = A1;       /*!< Default Y-direction analog pin */
const uint8_t DefaultAnalogJoystickButtonPin = 12;  /*!< Default select button digital pin */

/*!
  \brief Analog Joystick class
  This class implements analog joystick based on two 10k potentiometers and a button
 */
class AnalogJoystick: public AbstractKeyboard {

public:
  AnalogJoystick(
    uint8_t XPin = DefaultAnalogJoystickXPin,         /*!< X-direction potentiometer analog pin */
    uint8_t YPin = DefaultAnalogJoystickYPin,         /*!< Y-direction potentiometer analog pin */
    uint8_t ButtonPin = DefaultAnalogJoystickButtonPin  /*!< Select button digital pin */
  ): AbstractKeyboard(),
    m_XPin(XPin),
    m_YPin(YPin),
    m_ButtonPin(ButtonPin) { Init(); }
  virtual ~AnalogJoystick() override { Exit(); }

  virtual uint8_t GetKey() override;

protected:
  uint8_t m_XPin;       /*!< X-direction potentiometer analog pin */
  uint8_t m_YPin;       /*!< Y-direction potentiometer analog pin */
  uint8_t m_ButtonPin;  /*!< Select button digital pin */

private:
  bool Init();
  void Exit();
};
